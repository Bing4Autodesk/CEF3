// -*- C++ -*-
// Module:  Log4CPLUS
// File:    loggingevent.h

/** @file */

#ifndef LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_
#define LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_

#include "platform.h"

#include <memory>
#include "loglevel.h"
#include "timehelper.h"

namespace log4cplus { 
	class TimeHelper;
	/**
	* The internal representation of logging events. When an affirmative
	* decision is made to log then a <code>InternalLoggingEvent</code>
	* instance is created. This instance is passed around to the
	* different log4cplus components.
	*
	* This class is of concern to those wishing to extend log4cplus.
	*/
	class LOG4CPLUS_EXPORT InternalLoggingEvent 
	{
	public:
		// Ctors
		/**
		* Instantiate a LoggingEvent from the supplied parameters.
		*
		* @param logger   The logger of this loggingEvent.
		* @param loglevel The LogLevel of this loggingEvent.TimeHelper
		* @param message  The message of this loggingEvent.
		* @param filename Name of file where this loggingEvent has occurred,
		* can be NULL.
		* @param line     Line number in file specified by
		*                 the <code>filename</code> parameter.
		* @param function Name of function that is logging this loggingEvent.
		*/
		InternalLoggingEvent(const std::string& logger, LogLevel loglevel, 
				const std::string& message, const char* filename, int line, const char * _function = NULL);

		InternalLoggingEvent(const std::string& logger, LogLevel loglevel,
			const std::string& message, 
			TimeHelper time, const std::string& file,
			int line, const std::string& _function = std::string());

		InternalLoggingEvent();

		InternalLoggingEvent(const InternalLoggingEvent& rhs);

		virtual ~InternalLoggingEvent();

		void setLoggingEvent(const std::string& logger, LogLevel ll, const std::string& message,
				const char * filename, int line, const char * _function = NULL);

		// public virtual methods
		/** The application supplied message of logging loggingEvent. */
		virtual const std::string& getMessage() const;

		/** Returns the 'type' of InternalLoggingEvent.  Derived classes
		*  should override this method. (NOTE: Values <= 1000 are
		*  reserved for log4cplus and should not be used.)
		*/
		virtual unsigned int getType() const;

		/** Returns a copy of this object.  Derived classes
		*  should override this method.
		*/
		virtual std::auto_ptr<InternalLoggingEvent> clone() const;



		// public methods
		/** The logger of the logging loggingEvent. It is set by
		*  the LoggingEvent constructor.
		*/
		const std::string& getLoggerName() const
		{
			return _loggerName;
		}

		/** LogLevel of logging loggingEvent. */
		LogLevel getLogLevel() const
		{
			return _ll;
		}

		/** The number of milliseconds elapsed from 1/1/1970 until
		*  logging loggingEvent was created. */
		const TimeHelper& getTimestamp() const
		{
			return _timestamp;
		}

		/** The is the file where this log statement was written */
		const std::string& getFile() const
		{
			return _file;
		}

		/** The is the line where this log statement was written */
		int getLine() const { return _line; }

		std::string const& getFunction() const
		{
			return _function;
		}

		void swap(InternalLoggingEvent &);

		// public operators
		InternalLoggingEvent&
			operator=(const InternalLoggingEvent& rhs);

		// static methods
		static unsigned int getDefaultType();

	protected:
		// Data
		std::string _message;
		std::string _loggerName;
		LogLevel _ll;
		TimeHelper _timestamp;
		std::string _file;
		std::string _function;
		int _line;
	};

} // end namespace log4cplus

#endif // LOG4CPLUS_SPI_INTERNAL_LOGGING_EVENT_HEADER_
