// Module:  Log4CPLUS
// File:    rootlogger.cpp

#include "include/log/rootlogger.h"
#include "include/log/loglog.h"

using namespace log4cplus;


RootLogger::RootLogger(Hierarchy& h, LogLevel loglevel) : LoggerImpl("root", h)
{
	setLogLevel(loglevel);
}


LogLevel RootLogger::getAssignedLogLevel() const
{
	return _ll;
}

void RootLogger::setLogLevel(LogLevel loglevel)
{
	if(loglevel == NOT_SET_LOG_LEVEL) 
	{
		getLogLog().error("You have tried to set NOT_SET_LOG_LEVEL to root.");
	}
	else 
	{
		LoggerImpl::setLogLevel(loglevel);
	}
}

