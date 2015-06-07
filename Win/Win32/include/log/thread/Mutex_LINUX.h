//
// Mutex_POSIX.h
//


#ifndef Foundation_Mutex_POSIX_INCLUDED
#define Foundation_Mutex_POSIX_INCLUDED


#include "../platform.h"

#include <stdexcept>
#include <pthread.h>
#include <errno.h>




namespace log4cplus {


class LOG4CPLUS_EXPORT MutexImpl
{
protected:
	MutexImpl();
	MutexImpl(bool fast);
	~MutexImpl();
	void lockImpl();
	bool tryLockImpl();
	void unlockImpl();
	
private:
	pthread_mutex_t _mutex;
};


class LOG4CPLUS_EXPORT FastMutexImpl: public MutexImpl
{
protected:
	FastMutexImpl();
	~FastMutexImpl();
};


//
// inlines
//
inline void MutexImpl::lockImpl()
{
	if (pthread_mutex_lock(&_mutex)) 
		throw std::runtime_error("cannot lock mutex");
}


inline bool MutexImpl::tryLockImpl()
{
	int rc = pthread_mutex_trylock(&_mutex);
	if (rc == 0)
		return true;
	else if (rc == EBUSY)
		return false;
	else
		throw std::runtime_error("cannot lock mutex");
}


inline void MutexImpl::unlockImpl()
{
	if (pthread_mutex_unlock(&_mutex))
		throw std::runtime_error("cannot unlock mutex");
}


} // namespace log4cplus 


#endif // Foundation_Mutex_POSIX_INCLUDED
