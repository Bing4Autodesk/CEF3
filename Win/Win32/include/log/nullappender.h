// -*- C++ -*-
// Module:  Log4CPLUS
// File:    nullappender.h


/** @file */

#ifndef LOG4CPLUS_NULL_APPENDER_HEADER_
#define LOG4CPLUS_NULL_APPENDER_HEADER_

#include "platform.h"
#include "appender.h"


namespace log4cplus {

	/**
	* Appends log events to a file. 
	*/
	class LOG4CPLUS_EXPORT NullAppender : public Appender {
	public:
		// Ctors
		NullAppender();
		NullAppender(const log4cplus::Properties&);

		// Dtor
		virtual ~NullAppender();

		// Methods
		virtual void close();

	protected:
		virtual void append(const log4cplus::InternalLoggingEvent& loggingEvent);

	private:
		// Disallow copying of instances of this class
		NullAppender(const NullAppender&);
		NullAppender& operator= (const NullAppender&);
	};

} // end namespace log4cplus

#endif // LOG4CPLUS_NULL_APPENDER_HEADER_

