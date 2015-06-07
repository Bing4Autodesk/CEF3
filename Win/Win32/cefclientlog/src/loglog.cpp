// Module:  Log4CPLUS
// File:    loglog.cpp



#include "include/log/loglog.h"
#include "include/log/environment.h"
#include "include/log/consoleappender.h"
#include <ostream>
#include <stdexcept>

using namespace std;
using namespace log4cplus;

static char const PREFIX[] = "log4cplus: ";
static char const WARN_PREFIX[] = "log4cplus:WARN ";
static char const ERR_PREFIX[] = "log4cplus:ERROR ";


LogLog* LogLog::getLogLog()
{
    return &log4cplus::getLogLog();
}


LogLog::LogLog() : _isDebugEnabled(false), _isQuietMode(false) {}

LogLog::~LogLog() {}

void LogLog::setInternalDebugging(bool enabled)
{
     Mutex::ScopedLock lock(_mutex);

    _isDebugEnabled = enabled ;
}

void LogLog::setQuietMode(bool quietMode)
{
     Mutex::ScopedLock lock(_mutex);

    _isQuietMode = quietMode;
}

void LogLog::debug(const string& msg) const
{
    loggingWorker(PREFIX, msg);
}


void LogLog::debug(char const* msg) const
{
    loggingWorker(PREFIX, msg);
}

void LogLog::warn(const string& msg) const
{
    loggingWorker(WARN_PREFIX, msg);
}

void LogLog::warn(char const* msg) const
{
    loggingWorker(WARN_PREFIX, msg);
}


void LogLog::error(const string& msg, bool throw_flag) const
{
    loggingWorker(ERR_PREFIX, msg, throw_flag);
}

void LogLog::error(char const* msg, bool throw_flag) const
{
    loggingWorker(ERR_PREFIX, msg, throw_flag);
}

bool LogLog::getNotQuietMode() const
{
    return !_isQuietMode;
}

bool LogLog::getDebugMode() const
{
    return _isDebugEnabled && !_isQuietMode;
}

void LogLog::loggingWorker(char const* prefix, string const& msg, bool throw_flag) const
{
    if(!_isQuietMode)
    {
        // XXX This is potential recursive lock of
        // ConsoleAppender::outputMutex.
		Mutex::ScopedLock lock(const_cast<Mutex&>(ConsoleAppender::getOutputMutex()));
		std::cout << prefix << msg << std::endl;
    }

    if(throw_flag)
        throw std::runtime_error(msg);
}
 
