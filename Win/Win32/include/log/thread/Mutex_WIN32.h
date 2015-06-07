//
// Mutex_WIN32.h
//



#ifndef Foundation_Mutex_WIN32_INCLUDED
#define Foundation_Mutex_WIN32_INCLUDED


#include "../platform.h"



namespace log4cplus { 


class MutexImpl
{
protected:
	MutexImpl();
	~MutexImpl();
	void lockImpl();
	bool tryLockImpl();
	void unlockImpl();
	
private:
	CRITICAL_SECTION _cs;
};


typedef MutexImpl FastMutexImpl;


//
// inlines
//
inline void MutexImpl::lockImpl()
{
	try
	{
		EnterCriticalSection(&_cs);
	}
	catch (...)
	{
		throw std::runtime_error("cannot lock mutex");
	}
		
}


inline bool MutexImpl::tryLockImpl()
{
	try
	{
		return TryEnterCriticalSection(&_cs) != 0;
	}
	catch (...)
	{
		throw std::runtime_error("cannot lock mutex");
	}
}


inline void MutexImpl::unlockImpl()
{
	LeaveCriticalSection(&_cs);
}


} // namespace log4cplus


#endif // Foundation_Mutex_WIN32_INCLUDED
