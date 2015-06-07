// Module:  Log4CPLUS
// File:    ospappender.cxx

#ifdef LOG4CPLUS_USE_OSP

#include "include/log/layout.h"
#include "include/log/ospappender.h"
#include "include/log/loglog.h"
#include "include/log/stringhelper.h"
#include "include/log/loggingevent.h"
#include "include/log/osp/osp.h"
#include <strstream>

using namespace std;
using namespace log4cplus;


OspAppender::OspAppender()
{
}


OspAppender::OspAppender(const Properties& properties) : Appender(properties)
{
}


OspAppender::~OspAppender()
{
    destructorImpl();
}


void OspAppender::close()
{
	_isClosed = true;
}


// This method does not need to be locked since it is called by
// doAppend() which performs the locking
void OspAppender::append(const InternalLoggingEvent& loggingEvent)
{
    ostrstream output;
    _layout->formatAndAppend(output, loggingEvent);

	string outstring = output.str();

	OspPrintf(TRUE, FALSE, const_cast<char*>(outstring.c_str()));
}

#endif
