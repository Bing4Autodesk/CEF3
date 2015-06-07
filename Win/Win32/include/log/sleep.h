// -*- C++ -*-
// Module:  Log4CPLUS
// File:    sleep.h


/** @file */

#ifndef LOG4CPLUS_HELPERS_SLEEP_HEADER_
#define LOG4CPLUS_HELPERS_SLEEP_HEADER_

#include "platform.h"

namespace log4cplus { 

	LOG4CPLUS_EXPORT void sleep(unsigned long secs, unsigned long nanosecs = 0);
	LOG4CPLUS_EXPORT void sleepmillis(unsigned long millis);
} // end namespace log4cplus

#endif // LOG4CPLUS_HELPERS_SLEEP_HEADER_

