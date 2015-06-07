// Module:  Log4CPLUS
// File:    global-init.cpp


#include "include/log/platform.h"

#include "include/log/logger.h"
#include "include/log/loglog.h"
#include "include/log/internal.h"
#include "include/log/thread/tls.h"
#include "include/log/loglog.h"
#include "include/log/factory.h"
#include "include/log/hierarchy.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "include/log/thread/Mutex.h"

using namespace log4cplus;
//!Default context.
struct DefaultContext
{
	Mutex			consoleMutex;
	LogLog			loglog;
	LogLevelManager logLevelManager;
	TimeHelper		baseLayoutTime;
	Hierarchy		hierarchy;
	AppenderFactoryRegistry appenderFactoryRegistry;
	LayoutFactoryRegistry	layoutFactoryRegistry;
	FilterFactoryRegistry	filterFactoryRegistry;
};


enum DCState
{ 
	DC_UNINITIALIZED,
	DC_INITIALIZED,
	DC_DESTROYED
};


static DCState s_defaultContextState;
static DefaultContext* s_defaultContext;


struct DestroyDefaultContext
{
	~DestroyDefaultContext()
	{
		delete s_defaultContext;
		s_defaultContext = 0;
		s_defaultContextState = DC_DESTROYED;
	}
}; 

static DestroyDefaultContext s_destroDefaultContext;


static void allocDC()
{
	assert(!s_defaultContext);
	assert(s_defaultContextState == DC_UNINITIALIZED);

	if(s_defaultContext)
		throw std::logic_error("allocDC() called with non-NULL default_context.");

	if(s_defaultContextState == DC_INITIALIZED)
		throw std::logic_error("allocDC() called in DC_INITIALIZED state.");

	s_defaultContext = new DefaultContext;

	if(s_defaultContextState == DC_DESTROYED)
	{
		s_defaultContext->loglog.error(
		"Re-initializing default context after it has already been destroyed.\n""The memory will be leaked.");
	}
	s_defaultContextState = DC_INITIALIZED;
}


static DefaultContext* getDC(bool isAlloc = true)
{
	if(!s_defaultContext && isAlloc)
		allocDC();
	return s_defaultContext;
}


Mutex const& getConsoleOutputMutex()
{
	return getDC()->consoleMutex;
}

LogLog& log4cplus::getLogLog()
{
	return getDC()->loglog;
}


TimeHelper const& log4cplus::getLayoutTimeBase()
{
	return getDC()->baseLayoutTime;
}


LogLevelManager& log4cplus::getLogLevelManager() 
{
	return getDC()->logLevelManager;
}


Hierarchy& log4cplus::getDefaultHierarchy()
{
	return getDC()->hierarchy;
}

AppenderFactoryRegistry& log4cplus::getAppenderFactoryRegistry()
{
	return getDC()->appenderFactoryRegistry;
}


LayoutFactoryRegistry & log4cplus::getLayoutFactoryRegistry()
{
	return getDC()->layoutFactoryRegistry;
}


FilterFactoryRegistry & log4cplus::getFilterFactoryRegistry()
{
	return getDC()->filterFactoryRegistry;
}


TLSKeyType log4cplus::gTLS_StorageKey;


//!Thread local storage clean up function for POSIX threads.
static void ptdCleanupFunc(void* arg)
{
	PerThreadData* const arg_ptd = static_cast<PerThreadData*>(arg);
	PerThreadData* const ptd = getPerThreadData(false);
	(void) ptd;

	// Either it is a dummy value or it should be the per thread data
	// pointer we get from internal::get_ptd().
	assert(arg == reinterpret_cast<void *>(1) || arg_ptd == ptd ||(!ptd && arg_ptd));

	if(arg == reinterpret_cast<void *>(1))
	{
		TLSSetValue(log4cplus::gTLS_StorageKey, 0);
	}
	else if(arg)
	{
		delete arg_ptd;
		TLSSetValue(log4cplus::gTLS_StorageKey, 0);
	}
	else
	{
		// In this case we fall through to threadCleanup() and it does
		// all the necessary work itself.
		;
	}

	log4cplus::threadCleanup();
}


static void threadSetup()
{
	getPerThreadData(true);
}


void log4cplus::initializeLog4cplus()
{
	static bool initialized = false;
	if(initialized)
		return;

	log4cplus::gTLS_StorageKey = TLSInit(ptdCleanupFunc);
	threadSetup();

	DefaultContext* dc = getDC(true);
	dc->baseLayoutTime = TimeHelper::gettimeofday();
	Logger::getRoot();
	initializeFactoryRegistry();

	initialized = true;
}

void log4cplus::threadCleanup()
{
	// Do thread-specific cleanup.
	PerThreadData* ptd = getPerThreadData(false);
	delete ptd;
	setPerThreadData(0);
}


#if defined(_MSC_VER)
static VOID CALLBACK initializeLog4cplusApcProc(ULONG_PTR /*dwParam*/)
{
	log4cplus::initializeLog4cplus();
	threadSetup();
}


static void queueLog4cplusInitializationThroughAPC()
{
	if(!QueueUserAPC(initializeLog4cplusApcProc, GetCurrentThread(), 0))
		throw std::runtime_error("QueueUserAPC() has failed");
}


static void NTAPI thread_callback(LPVOID /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpReserved*/)
{
	// Perform actions based on the reason for calling.
	switch(fdwReason)
	{ 
	case DLL_PROCESS_ATTACH:
		{
			queueLog4cplusInitializationThroughAPC();
			break;
		}

	case DLL_THREAD_ATTACH:
		{
			break;
		}

	case DLL_THREAD_DETACH:
		{
			log4cplus::threadCleanup();
			break;
		}

	case DLL_PROCESS_DETACH:
		{
			log4cplus::threadCleanup();
			TLSCleanup(log4cplus::gTLS_StorageKey);
			break;
		}
	} // switch
}

#endif




#if defined(_MSC_VER) 

	#if defined(LOG4CPLUS_BUILD_DLL)
	extern "C"
		BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
	{
		thread_callback(hinstDLL, fdwReason, lpReserved);

		return TRUE;  // Successful DLL_PROCESS_ATTACH.
	}

	#else
	struct log4cplus_initializer
	{
		log4cplus_initializer()	{}

		~log4cplus_initializer()
		{
			// Last thread cleanup.
			log4cplus::threadCleanup();
			log4cplus::TLSCleanup(log4cplus::gTLS_StorageKey);
		}
	} static initializer;

	#endif

#else		//__linux__

	struct log4cplus_initializer
	{
		log4cplus_initializer()
		{
			log4cplus::initializeLog4cplus();
		}

		~log4cplus_initializer()
		{
			// Last thread cleanup.
			log4cplus::threadCleanup();

			log4cplus::TLSCleanup(log4cplus::gTLS_StorageKey);
		}
	} static initializer;

#endif
