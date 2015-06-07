// -*- C++ -*-
// Module:  Log4CPLUS
// File:    loglog.h


/** @file */

#ifndef LOG4CPLUS_HELPERS_LOGLOG
#define LOG4CPLUS_HELPERS_LOGLOG

#include "platform.h"




#include "thread/Mutex.h"

namespace log4cplus { 

	/**
	* This class used to output log statements from within the log4cplus package.
	*
	* Log4cplus components cannot make log4cplus logging calls. However, it is
	* sometimes useful for the user to learn about what log4cplus is
	* doing. You can enable log4cplus internal logging by defining the
	* <b>log4cplus.configDebug</b> variable.
	*
	* All log4cplus internal debug calls go to <code>cout</code>
	* where as internal errormessages are sent to
	* <code>cerr</code>. All internal messages are prepended with
	* the string "log4clus: ".
	*/
	class LOG4CPLUS_EXPORT LogLog
	{
	public:
		//!Return type of getLogLog().

		/**
		* Returns a reference to the <code>LogLog</code> singleton.
		*/
		static LogLog* getLogLog();

		/**
		* Allows to enable/disable log4cplus internal logging.
		*/
		void setInternalDebugging(bool enabled);

		/**
		* In quite mode no LogLog generates strictly no output, not even
		* for errors. 
		*
		* @param quietMode A true for not
		*/
		void setQuietMode(bool quietMode);

		/**
		* This method is used to output log4cplus internal debug
		* statements. Output goes to <code>std::cout</code>.
		*/
		void debug(const std::string& msg) const;
		void debug(char const* msg) const;

		/**
		* This method is used to output log4cplus internal error
		* statements. There is no way to disable error
		* statements.  Output goes to
		* <code>std::cerr</code>. Optionally, this method can
		* throw std::runtime_error exception too.
		*/
		void error(const std::string& msg, bool throw_flag = false) const;
		void error(char const* msg, bool throw_flag = false) const;

		/**
		* This method is used to output log4cplus internal warning
		* statements. There is no way to disable warning statements.
		* Output goes to <code>std::cerr</code>.
		*/
		void warn(const std::string& msg) const;
		void warn(char const* msg) const;

		// Public ctor and dtor to be used only by internal::DefaultContext.
		LogLog();
		virtual ~LogLog();

	private:

		void loggingWorker(char const*, std::string const&, bool throw_flag = false) const;

		bool getNotQuietMode() const;
		bool getDebugMode() const;

		// Data
		mutable bool _isDebugEnabled;
		mutable bool _isQuietMode;
		Mutex _mutex;

		LogLog(const LogLog&);
		LogLog& operator =(LogLog const&);

	};

	LOG4CPLUS_EXPORT LogLog& getLogLog();

}  // end namespace log4cplus 


#endif // LOG4CPLUS_HELPERS_LOGLOG

