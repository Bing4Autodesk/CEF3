// -*- C++ -*-
// Module:  Log4CPLUS
// File:    appenderattachableimpl.h


#ifndef LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_
#define LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

#include "platform.h"

#include "pointer.h"
#include "appenderattachable.h"
#include "thread/Mutex.h"

#include <memory>
#include <vector>


namespace log4cplus {

	/**
	* This Interface is for attaching Appenders to objects.
	*/
	class LOG4CPLUS_EXPORT AppenderAttachableImpl : public log4cplus::AppenderAttachable
	{
	public:
		// Data
		Mutex appender_list_mutex;

		// Ctors
		AppenderAttachableImpl();

		// Dtor
		virtual ~AppenderAttachableImpl();

		// Methods
		/**
		* Add an appender.  If the appender is already in the list in
		* won't be added again.
		*/
		virtual void addAppender(SharedAppenderPtr newAppender);

		/**
		* Get all previously added appenders as an vectory.
		*/
		virtual SharedAppenderPtrList getAllAppenders();

		/**
		* Look for an attached appender named as <code>name</code>.
		*
		* Return the appender with that name if in the list. Return null
		* otherwise.  
		*/
		virtual SharedAppenderPtr getAppender(const std::string& name);

		/**
		* Remove all previously added appenders.
		*/
		virtual void removeAllAppenders();

		/**
		* Remove the appender passed as parameter from the list of appenders.
		*/
		virtual void removeAppender(SharedAppenderPtr appender);

		/**
		* Remove the appender with the name passed as parameter from the
		* list of appenders.  
		*/
		virtual void removeAppender(const std::string& name);

		/**
		* Call the <code>doAppend</code> method on all attached appenders.  
		*/
		int appendLoopOnAppenders(const InternalLoggingEvent& loggingEvent) const;

	protected:
		// Types
		typedef std::vector<SharedAppenderPtr> ListType;

		// Data
		/** Array of appenders. */
		ListType _appenderList;

	private:
		AppenderAttachableImpl(AppenderAttachableImpl const&);
		AppenderAttachableImpl & operator = (AppenderAttachableImpl const&);
	};  // end class AppenderAttachableImpl

}  // end namespace log4cplus 

#endif // LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

