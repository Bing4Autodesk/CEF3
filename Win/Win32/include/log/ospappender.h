// Module:  Log4CPLUS
// File:    ospappender.h


/** @file */

#ifndef _LOG4CPLUS_OSP_APPENDER_HEADER_
#define _LOG4CPLUS_OSP_APPENDER_HEADER_

#include "platform.h"

#ifdef LOG4CPLUS_USE_OSP
#include "appender.h"

namespace log4cplus {

	/**
	* Appends log events to osp. 
	*/
	class LOG4CPLUS_EXPORT OspAppender : public Appender
	{
	public:
		// Ctors
		OspAppender();
		OspAppender(const Properties& properties);

		// Dtor
		virtual ~OspAppender();

		// Methods
		virtual void close();

	protected:
		virtual void append(const InternalLoggingEvent& loggingEvent);

	private:
		// Disallow copying of instances of this class
		OspAppender(const OspAppender&);
		OspAppender& operator=(const OspAppender&);
	};

} // end namespace log4cplus

#endif // LOG4CPLUS_USE_OSP

#endif // _LOG4CPLUS_OSP_APPENDER_HEADER_

