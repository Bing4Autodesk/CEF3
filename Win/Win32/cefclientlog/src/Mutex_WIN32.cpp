//
// Mutex_WIN32.cpp
//



#include "include/log/thread/Mutex_WIN32.h"


namespace log4cplus {


MutexImpl::MutexImpl()
{
	// the fct has a boolean return value under WInnNt/2000/XP but not on Win98
	// the return only checks if the input address of &_cs was valid, so it is safe to omit it
	InitializeCriticalSectionAndSpinCount(&_cs, 4000);
}


MutexImpl::~MutexImpl()
{
	DeleteCriticalSection(&_cs);
}
} // namespace log4cplus
