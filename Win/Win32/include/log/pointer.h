// -*- C++ -*-
// Module:  Log4CPLUS
// File:    pointer.h


//
// Note: Some of this code uses ideas from "More Effective C++" by Scott
// Myers, Addison Wesley Longmain, Inc.,(c) 1996, Chapter 29, pp. 183-213
//

/** @file */

#ifndef LOG4CPLUS_HELPERS_POINTERS_HEADER_
#define LOG4CPLUS_HELPERS_POINTERS_HEADER_

#include "platform.h"
#include "thread/Mutex.h"

#include <cassert>


namespace log4cplus { 

	class LOG4CPLUS_EXPORT SharedObject
	{
	public:
		void addReference() const;
		void removeReference() const;

	protected:
		// Ctor
		SharedObject() : _access_mutex(), _count(0) {}

		SharedObject(const SharedObject&) : _access_mutex(), _count(0) {}

		// Dtor
		virtual ~SharedObject();

		// Operators
		SharedObject& operator=(const SharedObject&) { return *this; }

	public:
		Mutex _access_mutex;


	private:

#if defined(_MSC_VER)
		typedef long count_type;
#else
		typedef unsigned count_type;
#endif
		mutable count_type _count;
	};


	template<class T>
	class SharedObjectPtr
	{
	public:
		// Ctor
		explicit SharedObjectPtr(T* realPtr = 0) : _pointee(realPtr)
		{
			addref();
		}

		SharedObjectPtr(const SharedObjectPtr& rhs) : _pointee(rhs._pointee)
		{
			addref();
		}

		// Dtor
		~SharedObjectPtr()
		{
			if(_pointee)
				_pointee->removeReference();
		}

		// Operators
		bool operator==(const SharedObjectPtr& rhs) const { return(_pointee == rhs._pointee); }
		bool operator!=(const SharedObjectPtr& rhs) const { return(_pointee != rhs._pointee); }
		bool operator==(const T* rhs) const { return(_pointee == rhs); }
		bool operator!=(const T* rhs) const { return(_pointee != rhs); }
		T* operator->() const {assert(_pointee); return _pointee; }
		T& operator*() const {assert(_pointee); return *_pointee; }

		SharedObjectPtr& operator=(const SharedObjectPtr& rhs)
		{
			return this->operator =(rhs._pointee);
		}

		SharedObjectPtr& operator=(T* rhs)
		{
			SharedObjectPtr<T>(rhs).swap(*this);
			return *this;
		}

		// Methods
		T* get() const { return _pointee; }

		void swap(SharedObjectPtr & other) throw()
		{
			std::swap(_pointee, other._pointee);
		}

		typedef T *(SharedObjectPtr:: * unspec_bool_type)() const;
		operator unspec_bool_type() const
		{
			return _pointee ? &SharedObjectPtr::get : 0;
		}

		bool operator !() const
		{
			return !_pointee;
		}

	private:
		// Methods
		void addref() const
		{
			if(_pointee)
				_pointee->addReference();
		}

		// Data
		T* _pointee;
	};
}  // end namespace log4cplus 


#endif // LOG4CPLUS_HELPERS_POINTERS_HEADER_
