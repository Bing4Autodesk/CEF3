// Module:  Log4CPLUS
// File:    logloguser.cpp


#include "include/log/logloguser.h"
#include "include/log/loglog.h"

using namespace log4cplus;


LogLogUser::LogLogUser() {}

LogLogUser::LogLogUser(const LogLogUser&) {}

LogLogUser::~LogLogUser() {}

LogLog& LogLogUser::getLogLog() const
{
    return *LogLog::getLogLog();
}

LogLogUser& LogLogUser::operator= (const LogLogUser&)
{
    return *this;
}


