// -*- C++ -*-
// Module:  Log4CPLUS
// File:    internal.h



#ifndef LOG4CPLUS_INTERNAL_INTERNAL_HEADER_
#define LOG4CPLUS_INTERNAL_INTERNAL_HEADER_

#include "platform.h"

#include <memory>
#include <vector>
#include <sstream>
#include <cstdio>

#include "loggingevent.h"
#include "thread/tls.h"
#include "snprintf.h"


namespace log4cplus { 

	//!Per thread data.
	class PerThreadData
	{
	public:
		PerThreadData()
		{
			_fnull = 0;
		}
		~PerThreadData()
		{
			if(_fnull)
				std::fclose(_fnull);
		}
		InternalLoggingEvent _forcedLoggingEvent;
		std::FILE* _fnull;
		snprintfBuf _snprintfBuf;
	};

	extern TLSKeyType gTLS_StorageKey;

	inline void setPerThreadData(PerThreadData* p)
	{
		TLSSetValue(gTLS_StorageKey, p);
	}

	inline PerThreadData* allocPerThreadData()
	{
		PerThreadData* tmp = new PerThreadData;
		setPerThreadData(tmp);
		return tmp;
	}

	inline PerThreadData* getPerThreadData(bool alloc = true)
	{
		PerThreadData* ptd = reinterpret_cast<PerThreadData*>(TLSGetValue(gTLS_StorageKey));

		if(!ptd && alloc)
			return allocPerThreadData();

		return ptd;
	}

}  // namespace log4cplus 


#endif // LOG4CPLUS_INTERNAL_INTERNAL_HEADER_
