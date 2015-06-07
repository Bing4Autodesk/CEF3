// Module:  Log4CPLUS
// File:    appender.cpp


#include "include/log/appender.h"
#include "include/log/layout.h"
#include "include/log/loglog.h"
#include "include/log/pointer.h"
#include "include/log/stringhelper.h"
#include "include/log/property.h"
#include "include/log/factory.h"
#include "include/log/loggingevent.h"
#include "include/log/internal.h"
#include <stdexcept>

using namespace std;
using namespace log4cplus;

ErrorHandler::ErrorHandler() {}

ErrorHandler::~ErrorHandler() {}

///////////////////////////////////////////////////////////////////////////////
// log4cplus::OnlyOnceErrorHandler 
///////////////////////////////////////////////////////////////////////////////

OnlyOnceErrorHandler::OnlyOnceErrorHandler() : firstTime(true) {}

OnlyOnceErrorHandler::~OnlyOnceErrorHandler() {}

void OnlyOnceErrorHandler::error(const string& err)
{
	if(firstTime) 
	{
		getLogLog().error(err);
		firstTime = false;
	}
}

void OnlyOnceErrorHandler::reset()
{
	firstTime = true;
}


Appender::Appender()
	: _layout(new SimpleLayout()),
	_name(""),
	_threshold(NOT_SET_LOG_LEVEL),
	_errorHandler(new OnlyOnceErrorHandler),
	_isClosed(false)
{
}

Appender::Appender(const log4cplus::Properties & properties)
	: _layout(new SimpleLayout())
	, _name()
	, _threshold(NOT_SET_LOG_LEVEL)
	, _errorHandler(new OnlyOnceErrorHandler)
	, _isClosed(false)
{
	if(properties.exists("layout"))
	{
		string const& factoryName = properties.getProperty("layout");
		LayoutFactory* factory = getLayoutFactoryRegistry().get(factoryName);
		if(factory == 0) 
		{
			getLogLog().error("Cannot find LayoutFactory: " + factoryName );
			return;
		}

		Properties layoutProperties = properties.getPropertySubset("layout.");
		try 
		{
			std::auto_ptr<Layout> newLayout(factory->createObject(layoutProperties));
			if(newLayout.get() == 0)
			{
				getLogLog().error("Failed to create appender: " + factoryName);
			}
			else 
			{
				_layout = newLayout;
			}
		}
		catch(std::exception const& e) 
		{
			getLogLog().error("Error while creating Layout: " + string(e.what()));
			return;
		}

	}

	// Support for appender.Threshold in properties configuration file
	if(properties.exists("Threshold")) 
	{
		string tmp = properties.getProperty("Threshold");
		tmp = log4cplus::toUpper(tmp);
		_threshold = getLogLevelManager().fromString(tmp);
	}

	// Configure the filters
	Properties filterProps = properties.getPropertySubset("filters.");
	unsigned filterCount = 0;
	FilterPtr filterChain;
	string filterName;
	while(filterProps.exists(filterName = convertIntegerToString(++filterCount)))
	{
		string const& factoryName = filterProps.getProperty(filterName);
		FilterFactory* factory = getFilterFactoryRegistry().get(factoryName);

		if(!factory)
		{
			string err = "Appender::ctor()- Cannot find FilterFactory: ";
			getLogLog().error(err + factoryName);
			continue;
		}
		FilterPtr tmpFilter = factory->createObject(filterProps.getPropertySubset(filterName + "."));
		if(!tmpFilter)
		{
			string err = "Appender::ctor()- Failed to create filter: ";
			getLogLog().error(err + filterName);
		}
		if(!filterChain)
			filterChain = tmpFilter;
		else
			filterChain->appendFilter(tmpFilter);
	}
	setFilter(filterChain);
}

Appender::~Appender()
{
	LogLog& loglog = getLogLog();

	loglog.debug("Destroying appender named [" + _name + "].");

	if(!_isClosed)
		loglog.error("Derived Appender did not call destructorImpl().");
}


void Appender::destructorImpl()
{
	// An appender might be closed then destroyed. There is no point
	// in closing twice. It can actually be a wrong thing to do, e.g.,
	// files get rolled more than once.
	if(_isClosed)
		return;

	close();
	_isClosed = true;
}

bool Appender::isClosed() const
{
	return _isClosed;
}


void Appender::doAppend(const log4cplus::InternalLoggingEvent& loggingEvent)
{
	Mutex::ScopedLock lock(_access_mutex);

	if(_isClosed) 
	{
		getLogLog().error("Attempted to append to closed appender named [" + _name + "].");
		return;
	}

	// Check appender's threshold logging level.

	if(!isAsSevereAsThreshold(loggingEvent.getLogLevel()))
		return;

	// Evaluate filters attached to this appender.

	if(checkFilter(_filter.get(), loggingEvent) == DENY)
		return;
	// Finally append given loggingEvent.

	append(loggingEvent);
}


string Appender::getName()
{
	return _name;
}

void Appender::setName(const string& n)
{
	this->_name = n;
}

ErrorHandler* Appender::getErrorHandler()
{
	return _errorHandler.get();
}

void Appender::setErrorHandler(std::auto_ptr<ErrorHandler> eh)
{
	if(!eh.get())
	{
		// We do not throw exception here since the cause is probably a
		// bad config file.
		getLogLog().warn("You have tried to set a null error-handler.");
		return;
	}

	Mutex::ScopedLock lock(_access_mutex);

	this->_errorHandler = eh;
}

void Appender::setLayout(std::auto_ptr<Layout> lo)
{
	Mutex::ScopedLock lock(_access_mutex);

	this->_layout = lo;
}

Layout* Appender::getLayout()
{
	return _layout.get();
}

