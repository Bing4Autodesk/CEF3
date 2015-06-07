// Module:  Log4CPLUS
// File:    factory.cpp


#include "include/log/factory.h"
#include "include/log/loggerfactory.h"
#include "include/log/loglog.h"
#include "include/log/property.h"
#include "include/log/consoleappender.h"
#include "include/log/fileappender.h"
#include "include/log/nullappender.h"
#include "include/log/ospappender.h"


using namespace log4cplus;
    

BaseFactory::~BaseFactory() {}

AppenderFactory::AppenderFactory() {}

AppenderFactory::~AppenderFactory() {}

LayoutFactory::LayoutFactory() {}

LayoutFactory::~LayoutFactory() {}

FilterFactory::FilterFactory() {}

FilterFactory::~FilterFactory()	{}

LoggerFactory::~LoggerFactory()	{}



void log4cplus::initializeFactoryRegistry()
{
    AppenderFactoryRegistry& reg = getAppenderFactoryRegistry();
    LOG4CPLUS_REG_APPENDER(reg, ConsoleAppender);
    LOG4CPLUS_REG_APPENDER(reg, NullAppender);
    LOG4CPLUS_REG_APPENDER(reg, FileAppender);
    LOG4CPLUS_REG_APPENDER(reg, RollingFileAppender);
    LOG4CPLUS_REG_APPENDER(reg, DailyRollingFileAppender);

#ifdef LOG4CPLUS_USE_OSP
	LOG4CPLUS_REG_APPENDER(reg, OspAppender);
#endif

    LayoutFactoryRegistry& reg2 = getLayoutFactoryRegistry();
    LOG4CPLUS_REG_LAYOUT(reg2, SimpleLayout);
    LOG4CPLUS_REG_LAYOUT(reg2, PatternLayout);

    FilterFactoryRegistry& reg3 = getFilterFactoryRegistry();
    LOG4CPLUS_REG_FILTER(reg3, DenyAllFilter);
    LOG4CPLUS_REG_FILTER(reg3, LogLevelMatchFilter);
    LOG4CPLUS_REG_FILTER(reg3, LogLevelRangeFilter);
}

