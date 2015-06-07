//
// Mutex.cpp
//


#include "include/log/thread/Mutex.h"

#ifdef _MSC_VER
#include "include/log/thread/Mutex_WIN32.h"
#else
#include "Mutex_LINUX.cpp"
#endif


using namespace log4cplus;

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

