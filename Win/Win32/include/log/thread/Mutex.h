//
// Mutex.h
//

#ifndef Foundation_Mutex_INCLUDED
#define Foundation_Mutex_INCLUDED

#include "../platform.h"
#include "ScopedLock.h"

#ifdef _MSC_VER
	#include "Mutex_WIN32.h"
#else
	#include "Mutex_LINUX.h"
#endif

namespace log4cplus {


class Mutex: private MutexImpl
	/// A Mutex (mutual exclusion) is a synchronization 
	/// mechanism used to control access to a shared resource
	/// in a concurrent (multithreaded) scenario.
	/// Mutexes are recursive, that is, the same mutex can be 
	/// locked multiple times by the same thread (but, of course,
	/// not by other threads).
	/// Using the ScopedLock class is the preferred way to automatically
	/// lock and unlock a mutex.
{
public:
	typedef log4cplus::ScopedLock<Mutex> ScopedLock;
	
	Mutex();
		/// creates the Mutex.
		
	~Mutex();
		/// destroys the Mutex.

	void lock();
		/// Locks the mutex. Blocks if the mutex
		/// is held by another thread.

	bool tryLock();
		/// Tries to lock the mutex. Returns false immediately
		/// if the mutex is already held by another thread.
		/// Returns true if the mutex was successfully locked.

	void unlock();
		/// Unlocks the mutex so that it can be acquired by
		/// other threads.
	
private:
	Mutex(const Mutex&);
	Mutex& operator = (const Mutex&);
};


class NullMutex
	/// A NullMutex is an simple mutex implementation
	/// which performs no locking at all. Useful in policy driven design
	/// where the type of mutex used can be now a template parameter allowing 
	/// to switch between thread-safe and not thread-safe implementations.
{
public:
	typedef log4cplus::ScopedLock<NullMutex> ScopedLock;
	
	NullMutex()
		/// Creates the NullMutex.
	{
	}
		
	~NullMutex()
		/// Destroys the NullMutex.
	{
	}

	void lock()
		/// Does nothing.
	{
	}
		
	void lock(long)
		/// Does nothing.
	{
	}

	bool tryLock()
		/// Does nothing and always returns true.
	{
		return true;
	}

	bool tryLock(long)
		/// Does nothing and always returns true.
	{
		return true;
	}

	void unlock()
		/// Does nothing.
	{
	}
};


//
// inlines
//
inline void Mutex::lock()
{
	lockImpl();
}


inline bool Mutex::tryLock()
{
	return tryLockImpl();
}


inline void Mutex::unlock()
{
	unlockImpl();
}

} // namespace log4cplus 


#endif // Foundation_Mutex_INCLUDED
