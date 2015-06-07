// Module:  Log4CPLUS
// File:    appenderattachableimpl.cpp



#include "include/log/appender.h"
#include "include/log/appenderattachableimpl.h"
#include "include/log/loglog.h"
#include "include/log/loggingevent.h"

#include <algorithm>

using namespace std;
using namespace log4cplus;


AppenderAttachable::~AppenderAttachable() {}


AppenderAttachableImpl::AppenderAttachableImpl() {}


AppenderAttachableImpl::~AppenderAttachableImpl() {}


void AppenderAttachableImpl::addAppender(SharedAppenderPtr newAppender)
{
	if(newAppender == NULL) 
	{
		getLogLog().warn("Tried to add NULL appender");
		return;
	}

	Mutex::ScopedLock lock(appender_list_mutex);

	ListType::iterator it = std::find(_appenderList.begin(), _appenderList.end(), newAppender);
	if(it == _appenderList.end()) 
	{
		_appenderList.push_back(newAppender);
	}
}


AppenderAttachableImpl::ListType AppenderAttachableImpl::getAllAppenders()
{
	Mutex::ScopedLock lock(appender_list_mutex);

	return _appenderList;
}


SharedAppenderPtr AppenderAttachableImpl::getAppender(const string& name)
{
	Mutex::ScopedLock lock(appender_list_mutex);

	for(ListType::iterator it=_appenderList.begin(); it!=_appenderList.end(); ++it)
	{
		if((*it)->getName() == name) {
			return *it;
		}
	}

	return SharedAppenderPtr(NULL);
}



void AppenderAttachableImpl::removeAllAppenders()
{
	Mutex::ScopedLock lock(appender_list_mutex);

	_appenderList.erase(_appenderList.begin(), _appenderList.end());
}



void AppenderAttachableImpl::removeAppender(SharedAppenderPtr appender)
{
	if(appender == NULL) {
		getLogLog().warn("Tried to remove NULL appender");
		return;
	}

	Mutex::ScopedLock lock(appender_list_mutex);

	ListType::iterator it =
		std::find(_appenderList.begin(), _appenderList.end(), appender);
	if(it != _appenderList.end()) 
	{
		_appenderList.erase(it);
	}
}



void AppenderAttachableImpl::removeAppender(const string& name)
{
	removeAppender(getAppender(name));
}



int AppenderAttachableImpl::appendLoopOnAppenders(const InternalLoggingEvent& loggingEvent) const
{
	int count = 0;

	Mutex::ScopedLock lock(const_cast<Mutex&>(appender_list_mutex));

	for(ListType::const_iterator it=_appenderList.begin(); it!=_appenderList.end(); ++it)
	{
		++count;
		(*it)->doAppend(loggingEvent);
	}

	return count;
}

