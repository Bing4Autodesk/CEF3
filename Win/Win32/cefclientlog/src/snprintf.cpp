

#include "include/log/snprintf.h"
#include "include/log/loglog.h"
#include "include/log/internal.h"
#include <cstdarg>
#include <cstdio>
#include <stdarg.h>
#include <wchar.h>
#include <stdio.h>

using namespace std;
using namespace log4cplus;


std::size_t const START_BUF_SIZE = 512;

#if defined(_MSC_VER)
char const NULL_FILE[] = "NUL";
#else
char const NULL_FILE[] = "/dev/null";
#endif


static inline int vftprintf(std::FILE * file, char const* fmt, std::va_list args)
{

#if defined(_MSC_VER)
	return vfprintf_s(file, fmt, args);
#else
	return std::vfprintf(file, fmt, args);
#endif
}

static inline int vstprintf(char * dest, std::size_t dest_size, char const* fmt, std::va_list args)
{
	int ret;

#if defined(_MSC_VER)
	ret = vsprintf_s(dest, dest_size, fmt, args);
#else
	ret = std::vsprintf(dest, fmt, args);
#endif

	if(ret >= 0)
		assert(static_cast<std::size_t>(ret) <= dest_size);

	return ret;
}



snprintfBuf::snprintfBuf() : _szBuf(START_BUF_SIZE)
{}


char const* snprintfBuf::print(char const* fmt, ...)
{
	assert(fmt);

	char const* str = 0;
	int ret = 0;
	std::va_list args;

	do
	{
		va_start(args, fmt);
		ret = printVaList(str, fmt, args);
		va_end(args);
	}
	while(ret == -1);

	return str;
}


int snprintfBuf::printVaList(char const*& str, char const* fmt, std::va_list args)
{
	int printed;
	std::size_t const fmt_len = std::char_traits<char>::length(fmt);
	std::size_t buf_size = _szBuf.size();
	std::size_t const output_estimate = fmt_len + fmt_len / 2 + 1;
	if(output_estimate > buf_size)
		_szBuf.resize(buf_size = output_estimate);

	std::FILE*& fnull = getPerThreadData()->_fnull;
	if(!fnull)
	{
		fnull = std::fopen(NULL_FILE, "wb");
		if(!fnull)
			LogLog::getLogLog()->error("Could not open NULL_FILE.", true);
	}

	printed = vftprintf(fnull, fmt, args);
	if(printed == -1)
		LogLog::getLogLog()->error("Error printing into NULL_FILE.", true);

	_szBuf.resize(printed + 1);
	int sprinted = vstprintf(&_szBuf[0], _szBuf.size(), fmt, args);
	if(sprinted == -1 || sprinted >=(int)_szBuf.size())
		LogLog::getLogLog()->error("Error printing into string.", true);

	assert(printed == sprinted);

	_szBuf[sprinted] = 0;

	str = &_szBuf[0];
	return printed;
}

