// -*- C++ -*-


#ifndef LOG4CPLUS_HELPERS_SNPRINTF_H
#define LOG4CPLUS_HELPERS_SNPRINTF_H

#include "platform.h"

#include <cstdarg>
#include <vector>


namespace log4cplus { 


class LOG4CPLUS_EXPORT snprintfBuf
{
public:
    snprintfBuf();

    char const* print(char const* fmt, ...);
    int printVaList(char const*& str, char const* fmt, std::va_list args);

private:
    std::vector<char> _szBuf;
};
  
}  // namespace log4cplus 



#endif // LOG4CPLUS_HELPERS_SNPRINTF_H
