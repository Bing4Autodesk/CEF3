// Module:  Log4CPLUS
// File:    pointer.cpp



#include "include/log/pointer.h"

#include <cassert>

using namespace log4cplus;


SharedObject::~SharedObject()
{
	assert(_count == 0);
}



void SharedObject::addReference() const
{

#if defined (_MSC_VER) 
	_InterlockedIncrement (&_count);

#else
	Mutex::ScopedLock lock(const_cast<Mutex&>(_access_mutex));
	++_count;

#endif
}


void SharedObject::removeReference() const
{
	assert (_count > 0);
	bool isDestroy;

#if defined (_MSC_VER) 
	isDestroy = _InterlockedDecrement (&_count) == 0;

#else
	{
		Mutex::ScopedLock lock(const_cast<Mutex&>(_access_mutex));
		isDestroy = --_count == 0;
	}

#endif
	if (isDestroy)
		delete this;
}

