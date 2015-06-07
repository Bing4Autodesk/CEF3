// Module:  Log4CPLUS
// File:    loggingmacros.cpp


/** @file
* This file implements support function for loggingmacros.h file. */

#include "include/log/internal.h"
#include "include/log/loggingmacros.h"

using namespace std;
using namespace log4cplus;


snprintfBuf & log4cplus::macro_getStringBuf()
{
	return getPerThreadData()->_snprintfBuf;
}

void log4cplus::macro_forcedLog(Logger const& logger, LogLevel logLevel, 
	string const& msg, char const* filename, int line, char const* func)
{
	InternalLoggingEvent& loggingEvent = getPerThreadData()->_forcedLoggingEvent;
	loggingEvent.setLoggingEvent(logger.getName(), logLevel, msg, filename, line, func);
	logger.forcedLog(loggingEvent);
}

