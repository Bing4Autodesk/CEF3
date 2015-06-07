// -*- C++ -*-
// Module:  Log4CPLUS
// File:    loglevel.h

/** @file 
* This header defines the LogLevel type.
*/

#ifndef LOG4CPLUS_LOGLEVEL_HEADER_
#define LOG4CPLUS_LOGLEVEL_HEADER_

#include "platform.h"

#include <vector>



namespace log4cplus {

	/** 
	* \typedef int LogLevel
	* Defines the minimum set of priorities recognized by the system,
	* that is {@link #FATAL_LOG_LEVEL}, {@link #ERROR_LOG_LEVEL}, {@link
	* #WARN_LOG_LEVEL}, {@link #INFO_LOG_LEVEL}, {@link #DEBUG_LOG_LEVEL}, 
	* and {@link #TRACE_LOG_LEVEL}.
	*/
	//  typedef int LogLevel;

	enum LogLevel 
	{
		/** \var OFF_LOG_LEVEL
		* The <code>OFF_LOG_LEVEL</code> LogLevel is used during configuration to
		* turn off logging. */
		OFF_LOG_LEVEL     = 60000,

		/** \var FATAL_LOG_LEVEL
		* The <code>FATAL_LOG_LEVEL</code> LogLevel designates very severe error
		* events that will presumably lead the application to abort.  */
		FATAL_LOG_LEVEL   = 50000,

		/** \var ERROR_LOG_LEVEL
		* The <code>ERROR_LOG_LEVEL</code> LogLevel designates errorevents that
		* might still allow the application to continue running. */
		ERROR_LOG_LEVEL   = 40000,

		/** \var WARN_LOG_LEVEL
		* The <code>WARN_LOG_LEVEL</code> LogLevel designates potentially harmful 
		* situations. */
		WARN_LOG_LEVEL    = 30000,

		/** \var INFO_LOG_LEVEL
		* The <code>INFO_LOG_LEVEL</code> LogLevel designates informational 
		* messages  that highlight the progress of the application at 
		* coarse-grained  level. */
		INFO_LOG_LEVEL    = 20000,

		/** \var DEBUG_LOG_LEVEL
		* The <code>DEBUG_LOG_LEVEL</code> LogLevel designates fine-grained
		* informational events that are most useful to debug an application. */
		DEBUG_LOG_LEVEL   = 10000,

		/** \var TRACE_LOG_LEVEL
		* The <code>TRACE_LOG_LEVEL</code> LogLevel is used to "trace" entry
		* and exiting of methods. */
		TRACE_LOG_LEVEL   = 0,

		/** \var ALL_LOG_LEVEL
		* The <code>ALL_LOG_LEVEL</code> LogLevel is used during configuration to
		* turn on all logging. */
		ALL_LOG_LEVEL    = TRACE_LOG_LEVEL,

		/** \var NOT_SET_LOG_LEVEL
		* The <code>NOT_SET_LOG_LEVEL</code> LogLevel is used to indicated that
		* no particular LogLevel is desired and that the default should be used.
		*/
		NOT_SET_LOG_LEVEL = -1,
	};


	/**
	* This class is used to "manage" LogLevel definitions.  This class is also
	* how "derived" LogLevels are created. Here are the steps to creating a
	* "derived" LogLevel:
	*/
	class LOG4CPLUS_EXPORT LogLevelManager {
	public:
		LogLevelManager();
		~LogLevelManager();

		/**
		* This method is called by all Layout classes to convert a LogLevel
		* into a string.
		* 
		* Note: It traverses the list of <code>LogLevelToStringMethod</code>
		*       to do this, so all "derived" LogLevels are recognized as well.
		*/
		std::string const& toString(LogLevel ll) const;

		/**
		* This method is called by all classes internally to log4cplus to
		* convert a string into a LogLevel.
		* 
		* Note: It traverses the list of <code>StringToLogLevelMethod</code>
		*       to do this, so all "derived" LogLevels are recognized as well.
		*/
		LogLevel fromString(const std::string& s) const;

	private:
		// Data

		// Disable Copy
		LogLevelManager(const LogLevelManager&);
		LogLevelManager& operator= (const LogLevelManager&);
	};

	/**
	* Returns the singleton LogLevelManager.
	*/
	LOG4CPLUS_EXPORT LogLevelManager& getLogLevelManager();

}


#endif // LOG4CPLUS_LOGLEVEL_HEADER_

