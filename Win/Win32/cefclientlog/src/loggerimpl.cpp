// Module:  Log4CPLUS
// File:    loggerimpl.cpp


#include "include/log/internal.h"
#include "include/log/loggerimpl.h"
#include "include/log/appender.h"
#include "include/log/hierarchy.h"
#include "include/log/loglog.h"
#include "include/log/loggingevent.h"
#include "include/log/rootlogger.h"

using namespace std;
using namespace log4cplus;	


LoggerImpl::LoggerImpl(const string& name_, Hierarchy& h)
	: _name(name_), _ll(NOT_SET_LOG_LEVEL), _parent(NULL), _hierarchy(h)
{
}

LoggerImpl::~LoggerImpl() 
{ 
}

void LoggerImpl::callAppenders(const InternalLoggingEvent& loggingEvent)
{
	int writes = 0;
	for(const LoggerImpl* c = this; c != NULL; c=c->_parent.get())
	{
		writes += c->appendLoopOnAppenders(loggingEvent);
	}

	// No appenders in hierarchy, warn user only once.
	if(!_hierarchy._isEmittedNoAppenderWarning && writes == 0) 
	{
		getLogLog().error("No appenders could be found for logger(" + getName() + ").");
		getLogLog().error("Please initialize the log4cplus system properly.");
		_hierarchy._isEmittedNoAppenderWarning = true;
	}
}


void LoggerImpl::closeNestedAppenders()
{
	SharedAppenderPtrList appenders = getAllAppenders();
	for(SharedAppenderPtrList::iterator it=appenders.begin(); it!=appenders.end(); ++it)
	{
		Appender & appender = **it;
		if(!appender.isClosed())
			appender.close();
	}
}


bool LoggerImpl::isEnabledFor(LogLevel loglevel) const
{
	if(_hierarchy._nDisableValue >= loglevel) 
	{
		return false;
	}
	return loglevel >= getChainedLogLevel();
}


void LoggerImpl::log(LogLevel loglevel, const string& message, const char* file, int line, const char* _function)
{
	if(isEnabledFor(loglevel))
	{
		forcedLog(loglevel, message, file, line, _function ? _function : "");
	}
}

void LoggerImpl::log(InternalLoggingEvent const& ev)
{
	if(isEnabledFor(ev.getLogLevel()))
		forcedLog(ev);
}


LogLevel LoggerImpl::getChainedLogLevel() const
{
	for(const LoggerImpl *c=this; c != NULL; c=c->_parent.get()) 
	{
		if(c->_ll != NOT_SET_LOG_LEVEL) 
		{
			return c->_ll;
		}
	}

	getLogLog().error("LoggerImpl::getChainedLogLevel()- No valid LogLevel found", true);
	return NOT_SET_LOG_LEVEL;
}


Hierarchy& LoggerImpl::getHierarchy() const
{ 
	return _hierarchy; 
}


void LoggerImpl::forcedLog(LogLevel loglevel, const string& message,
	const char* file, int line, const char* _function)
{
	InternalLoggingEvent& loggingEvent = getPerThreadData()->_forcedLoggingEvent;
	assert(_function);
	loggingEvent.setLoggingEvent(this->getName(), loglevel, message, file, line, _function);
	callAppenders(loggingEvent);
}


void LoggerImpl::forcedLog(InternalLoggingEvent const& ev)
{
	callAppenders(ev);
}

