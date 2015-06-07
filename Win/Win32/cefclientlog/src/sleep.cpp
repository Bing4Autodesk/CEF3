// Module:  Log4CPLUS
// File:    sleep.cpp



#include "include/log/sleep.h"
#include "include/log/timehelper.h"

#include <cerrno>
#include <time.h>

using namespace log4cplus;


///////////////////////////////////////////////////////////////////////////////
// public methods
///////////////////////////////////////////////////////////////////////////////

int const MILLIS_TO_NANOS = 1000000;
int const SEC_TO_MILLIS = 1000;

void log4cplus::sleep(unsigned long secs, unsigned long nanosecs)
{
#if defined(_MSC_VER)
	DWORD const MAX_SLEEP_SECONDS = 4294966;        // (2**32-2)/1000

	DWORD nano_millis = nanosecs / static_cast<unsigned long>(MILLIS_TO_NANOS);
	if (secs <= MAX_SLEEP_SECONDS) 
	{
		Sleep((secs * SEC_TO_MILLIS) + nano_millis);
		return;
	}

	DWORD no_of_max_sleeps = secs / MAX_SLEEP_SECONDS;

	for(DWORD i = 0; i < no_of_max_sleeps; i++) 
	{
		Sleep(MAX_SLEEP_SECONDS * SEC_TO_MILLIS);
	}

	Sleep((secs % MAX_SLEEP_SECONDS) * SEC_TO_MILLIS + nano_millis);
#else
	timespec sleep_time;
	sleep_time.tv_sec = secs;
	sleep_time.tv_nsec = nanosecs;

	timespec remain;
	while (nanosleep(&sleep_time, &remain)) 
	{
		if (errno == EINTR) 
		{
			sleep_time.tv_sec  = remain.tv_sec;
			sleep_time.tv_nsec = remain.tv_nsec;               
			continue;
		}
		else 
		{
			return;
		}
	}
#endif
}


void log4cplus::sleepmillis(unsigned long millis)
{
	unsigned long secs = millis / SEC_TO_MILLIS;
	unsigned long nanosecs = (millis % SEC_TO_MILLIS) * MILLIS_TO_NANOS;
	log4cplus::sleep(secs, nanosecs);
}

