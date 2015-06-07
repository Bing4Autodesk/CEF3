// -*- C++ -*-
// Module:  Log4CPLUS
// File:    timehelper.h


/** @file */

#ifndef LOG4CPLUS_HELPERS_TIME_HELPER_HEADER_
#define LOG4CPLUS_HELPERS_TIME_HELPER_HEADER_

#include "platform.h"
#include "timehelper.h"
#include <ctime>


namespace log4cplus { 

	/**
	* This class represents a Epoch time with microsecond accuracy.
	*/
	class LOG4CPLUS_EXPORT TimeHelper 
	{
	public:
		TimeHelper();
		TimeHelper(std::time_t tv_sec, long tv_usec);
		explicit TimeHelper(std::time_t time);

		/**
		* Returns the current time using the <code>gettimeofday()</code>
		* method if it is available on the current platform.  (Not on 
		* WIN32.)
		*/
		static TimeHelper gettimeofday();

		// Methods
		/**
		* Returns <i>seconds</i> value.
		*/
		time_t sec() const { return _tv_seconds; }

		/**
		* Returns <i>microseconds</i> value.
		*/
		long usec() const { return _tv_microseconds; }

		/**
		* Sets the <i>seconds</i> value.
		*/
		void sec(std::time_t s) { _tv_seconds = s; }

		/**
		* Sets the <i>microseconds</i> value.
		*/
		void usec(long us) { _tv_microseconds = us; }

		/**
		* Sets this Time using the <code>mktime</code> function.
		*/
		time_t setTime(std::tm* t);

		/**
		* Returns this Time as a <code>time_t</code> value.
		*/
		time_t getTime() const;

		/**
		* Populates <code>tm</code> using the <code>localtime()</code>
		* function.
		*/
		void localtime(std::tm* t) const;

		/**
		* Returns a string with a "formatted time" specified by
		* <code>fmt</code>.  It used the <code>strftime()</code>
		* function to do this.  
		* 
		* Look at your platform's <code>strftime()</code> documentation
		* for the formatting options available.
		* 
		* The following additional options are provided:<br>
		* <code>%q</code> - 3 character field that provides milliseconds
		* <code>%Q</code> - 7 character field that provides fractional 
		* milliseconds.
		*/
		std::string getFormattedTime(const std::string& fmt) const;

		// Operators
		TimeHelper& operator+= (const TimeHelper& rhs);
		TimeHelper& operator-= (const TimeHelper& rhs);
		TimeHelper& operator/= (long rhs);
		TimeHelper& operator*= (long rhs);

	private:
		// Data
		time_t _tv_seconds;  /* seconds */
		long _tv_microseconds;  /* microseconds */
	};
} // namespace log4cplus



LOG4CPLUS_EXPORT const log4cplus::TimeHelper operator+(const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT const log4cplus::TimeHelper operator-(const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT const log4cplus::TimeHelper operator/(const log4cplus::TimeHelper& lhs, long rhs);

LOG4CPLUS_EXPORT const log4cplus::TimeHelper operator*(const log4cplus::TimeHelper& lhs, long rhs);

LOG4CPLUS_EXPORT bool operator < (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT bool operator <= (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT bool operator > (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT bool operator >= (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT bool operator == (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);

LOG4CPLUS_EXPORT bool operator != (const log4cplus::TimeHelper& lhs, const log4cplus::TimeHelper& rhs);




#endif // LOG4CPLUS_HELPERS_TIME_HELPER_HEADER_

