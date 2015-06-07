// Module:  Log4CPLUS
// File:    consoleappender.cpp

#include "include/log/platform.h"
#include "include/log/layout.h"
#include "include/log/consoleappender.h"

#include "include/log/loglog.h"
#include "include/log/stringhelper.h"
#include "include/log/property.h"
#include "include/log/loggingevent.h"
#include <ostream>

using namespace log4cplus;

extern log4cplus::Mutex const& getConsoleOutputMutex ();

log4cplus::Mutex const& ConsoleAppender::getOutputMutex ()
{
	return getConsoleOutputMutex();
}


ConsoleAppender::ConsoleAppender(bool immediateFlush_) : _immediateFlush(immediateFlush_) {}


ConsoleAppender::ConsoleAppender(const Properties & properties)
	: Appender(properties), _immediateFlush(false)
{
	properties.getBool (_immediateFlush, "ImmediateFlush");
}


ConsoleAppender::~ConsoleAppender()
{
	destructorImpl();
}


void ConsoleAppender::close()
{
	_isClosed = true;
}


void ConsoleAppender::append(const InternalLoggingEvent& loggingEvent)
{
	Mutex::ScopedLock lock(const_cast<Mutex&>(getOutputMutex()));

	_layout->formatAndAppend(std::cout, loggingEvent);
	if(_immediateFlush) 
	{
		std::cout.flush();
	}
}

