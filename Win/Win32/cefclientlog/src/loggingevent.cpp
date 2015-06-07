// Module:  Log4CPLUS
// File:    loggingevent.cpp


#include "include/log/loggingevent.h"
#include "include/log/internal.h"
#include <algorithm>

using namespace std;
using namespace log4cplus;


static const int LOG4CPLUS_DEFAULT_TYPE = 1;


InternalLoggingEvent::InternalLoggingEvent(const string& logger,
	LogLevel loglevel, const string& message_, const char* filename,
	int line_, const char * function_)
	: _message(message_)
	, _loggerName(logger)
	, _ll(loglevel)
	, _timestamp(TimeHelper::gettimeofday())
	, _file(filename ? string(filename) : string())
	, _function(function_ ? string(function_) : string())
	, _line(line_)
{
}

InternalLoggingEvent::InternalLoggingEvent(const string& logger,
	LogLevel loglevel, const string& message_, TimeHelper time,
	const string& file_, int line_, const string& function_)
	: _message(message_), _loggerName(logger)
	, _ll(loglevel), _timestamp(time)
	, _file(file_), _function(function_)
	, _line(line_)
{
}

InternalLoggingEvent::InternalLoggingEvent()
	: _ll(NOT_SET_LOG_LEVEL), _function(), _line(0)
{}

InternalLoggingEvent::InternalLoggingEvent(const InternalLoggingEvent& rhs)
	: _message(rhs.getMessage())
	, _loggerName(rhs.getLoggerName())
	, _ll(rhs.getLogLevel())
	, _timestamp(rhs.getTimestamp())
	, _file(rhs.getFile())
	, _function(rhs.getFunction())
	, _line(rhs.getLine())
{
}

InternalLoggingEvent::~InternalLoggingEvent()
{
}

///////////////////////////////////////////////////////////////////////////////
// InternalLoggingEvent static methods
///////////////////////////////////////////////////////////////////////////////

unsigned int InternalLoggingEvent::getDefaultType()
{
	return LOG4CPLUS_DEFAULT_TYPE;
}


void InternalLoggingEvent::setLoggingEvent(const string& logger, LogLevel loglevel, const string& msg, 
	const char * filename, int fline, const char * function_)
{
	// This could be imlemented using the swap idiom:
	//
	// InternalLoggingEvent(logger, loglevel, msg, filename, fline).swap(*this);
	//
	// But that defeats the optimization of using thread local instance
	// of InternalLoggingEvent to avoid memory allocation.

	_loggerName = logger;
	_ll = loglevel;
	_message = msg;
	_timestamp = TimeHelper::gettimeofday();

	if(filename)
		_file = string(filename);
	else
		_file.clear();

	if(function_)
		_function = string(function_);
	else
		_function.clear();

	_line = fline;
}

const string& InternalLoggingEvent::getMessage() const
{
	return _message;
}


unsigned int InternalLoggingEvent::getType() const
{
	return LOG4CPLUS_DEFAULT_TYPE;
}

std::auto_ptr<InternalLoggingEvent> InternalLoggingEvent::clone() const
{
	std::auto_ptr<InternalLoggingEvent> tmp(new InternalLoggingEvent(*this));
	return tmp;
}

InternalLoggingEvent & InternalLoggingEvent::operator = (const InternalLoggingEvent& rhs)
{
	InternalLoggingEvent(rhs).swap(*this);
	return *this;
}

void InternalLoggingEvent::swap(InternalLoggingEvent & other)
{
	using std::swap;

	swap(_message, other._message);
	swap(_loggerName, other._loggerName);
	swap(_ll, other._ll);
	swap(_timestamp, other._timestamp);
	swap(_file, other._file);
	swap(_function, other._function);
	swap(_line, other._line);
}

