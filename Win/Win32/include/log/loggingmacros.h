// -*- C++ -*-
// Module:  Log4CPLUS
// File:    loggingmacros.h

/** @file
 * This header defines the logging macros. */

#ifndef LOG4CPLUS_LOGGING_MACROS_HEADER_
#define LOG4CPLUS_LOGGING_MACROS_HEADER_

#include "platform.h"


#include "logger.h"
#include "snprintf.h"
#include <sstream>
#include <utility>


#if defined(_MSC_VER)
#define LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()  \
    __pragma(warning(push))                 \
    __pragma(warning(disable:4127))           

#define LOG4CPLUS_RESTORE_DOWHILE_WARNING()   \
    __pragma(warning(pop))

#else
#define LOG4CPLUS_SUPPRESS_DOWHILE_WARNING() /* empty */
#define LOG4CPLUS_RESTORE_DOWHILE_WARNING() /* empty */

#endif

#define LOG4CPLUS_DOWHILE_NOTHING()                 \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()            \
    do {} while(0)                                \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()

#if defined(LOG4CPLUS_DISABLE_FATAL) && !defined(LOG4CPLUS_DISABLE_ERROR)
#define LOG4CPLUS_DISABLE_ERROR
#endif
#if defined(LOG4CPLUS_DISABLE_ERROR) && !defined(LOG4CPLUS_DISABLE_WARN)
#define LOG4CPLUS_DISABLE_WARN
#endif
#if defined(LOG4CPLUS_DISABLE_WARN) && !defined(LOG4CPLUS_DISABLE_INFO)
#define LOG4CPLUS_DISABLE_INFO
#endif
#if defined(LOG4CPLUS_DISABLE_INFO) && !defined(LOG4CPLUS_DISABLE_DEBUG)
#define LOG4CPLUS_DISABLE_DEBUG
#endif
#if defined(LOG4CPLUS_DISABLE_DEBUG) && !defined(LOG4CPLUS_DISABLE_TRACE)
#define LOG4CPLUS_DISABLE_TRACE
#endif


namespace log4cplus
{
	
	
inline Logger macros_getLogger(Logger const& logger)
{
    return logger;
}


inline Logger const& macros_getLogger(Logger & logger)
{
    return logger;
}

inline Logger macros_getLogger(std::string const& logger)
{
    return Logger::getInstance(logger);
}


inline Logger macros_getLogger(char const* logger)
{
    return Logger::getInstance(logger);
}


LOG4CPLUS_EXPORT snprintfBuf & macro_getStringBuf();
LOG4CPLUS_EXPORT void macro_forcedLog(Logger const&, LogLevel, std::string const&, char const*, int, char const*);


} // namespace log4cplus


#define LOG4CPLUS_MACRO_BODY(logger, logEvent, logLevel)                \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        Logger const& constLogger  = macros_getLogger(logger);			\
        if(constLogger.isEnabledFor(logLevel)) {						\
			ostringstream buf;											\
            buf << logEvent;											\
            macro_forcedLog(constLogger, logLevel, buf.str(),			\
                __FILE__, __LINE__, __FUNCTION__);						\
        }                                                               \
    } while(0)                                                         \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()


#define LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, logLevel)            \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        Logger const& constLogger = macros_getLogger(logger);			\
        if(constLogger.isEnabledFor(logLevel)) {						\
            macro_forcedLog(constLogger, logLevel, logEvent,            \
                __FILE__, __LINE__, __FUNCTION__);						\
        }                                                               \
    } while(0)                                                          \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()

#define LOG4CPLUS_MACRO_FMT_BODY(logger, logLevel, logFmt, ...)         \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        Logger const& constLogger = macros_getLogger(logger);            \
        if(constLogger.isEnabledFor(logLevel)) {						\
			snprintfBuf& buf = macro_getStringBuf();					\
            char const* logEvent = buf.print(logFmt, __VA_ARGS__);      \
            macro_forcedLog(constLogger, logLevel, logEvent,             \
                __FILE__, __LINE__, __FUNCTION__);						\
        }                                                               \
    } while(0)                                                          \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()


/**
 * @def LOG4CPLUS_TRACE(logger, logEvent) This macro creates a
 * TraceLogger to log a TRACE_LOG_LEVEL message to <code>logger</code>
 * upon entry and exiting of a method.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_TRACE)
#define LOG4CPLUS_TRACE_METHOD(logger, logEvent)                        \
    TraceLogger _log4cplus_trace_logger(logger, logEvent,    \
        __FILE__, __LINE__, __FUNCTION__);

#define LOG4CPLUS_TRACE(logger, logEvent)                               \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, TRACE_LOG_LEVEL)

#define LOG4CPLUS_TRACE_STR(logger, logEvent)                           \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, TRACE_LOG_LEVEL)

#define LOG4CPLUS_TRACE_FMT(logger, logFmt, ...)                            \
    LOG4CPLUS_MACRO_FMT_BODY(logger, TRACE_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_TRACE_METHOD(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_TRACE(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_TRACE_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_TRACE_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif

/**
 * @def LOG4CPLUS_DEBUG(logger, logEvent)  This macro is used to log a
 * DEBUG_LOG_LEVEL message to <code>logger</code>.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_DEBUG)
#define LOG4CPLUS_DEBUG(logger, logEvent)                               \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, DEBUG_LOG_LEVEL)

#define LOG4CPLUS_DEBUG_STR(logger, logEvent)                           \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, DEBUG_LOG_LEVEL)

#define LOG4CPLUS_DEBUG_FMT(logger, logFmt, ...)                            \
    LOG4CPLUS_MACRO_FMT_BODY(logger, DEBUG_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_DEBUG(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_DEBUG_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_DEBUG_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif

/**
 * @def LOG4CPLUS_INFO(logger, logEvent)  This macro is used to log a
 * INFO_LOG_LEVEL message to <code>logger</code>.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_INFO)
#define LOG4CPLUS_INFO(logger, logEvent)                                \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, INFO_LOG_LEVEL)

#define LOG4CPLUS_INFO_STR(logger, logEvent)                            \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, INFO_LOG_LEVEL)

#define LOG4CPLUS_INFO_FMT(logger, logFmt, ...)                             \
    LOG4CPLUS_MACRO_FMT_BODY(logger, INFO_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_INFO(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_INFO_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_INFO_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif

/**
 * @def LOG4CPLUS_WARN(logger, logEvent)  This macro is used to log a
 * WARN_LOG_LEVEL message to <code>logger</code>.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_WARN)
#define LOG4CPLUS_WARN(logger, logEvent)                                \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, WARN_LOG_LEVEL)

#define LOG4CPLUS_WARN_STR(logger, logEvent)                            \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, WARN_LOG_LEVEL)

#define LOG4CPLUS_WARN_FMT(logger, logFmt, ...)                             \
    LOG4CPLUS_MACRO_FMT_BODY(logger, WARN_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_WARN(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_WARN_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_WARN_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif

/**
 * @def LOG4CPLUS_ERROR(logger, logEvent)  This macro is used to log a
 * ERROR_LOG_LEVEL message to <code>logger</code>.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_ERROR)
#define LOG4CPLUS_ERROR(logger, logEvent)                               \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, ERROR_LOG_LEVEL)
#define LOG4CPLUS_ERROR_STR(logger, logEvent)                           \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, ERROR_LOG_LEVEL)

#define LOG4CPLUS_ERROR_FMT(logger, logFmt, ...)                            \
    LOG4CPLUS_MACRO_FMT_BODY(logger, ERROR_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_ERROR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_ERROR_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_ERROR_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif

/**
 * @def LOG4CPLUS_FATAL(logger, logEvent)  This macro is used to log a
 * FATAL_LOG_LEVEL message to <code>logger</code>.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOG4CPLUS_DISABLE_FATAL)
#define LOG4CPLUS_FATAL(logger, logEvent)                               \
    LOG4CPLUS_MACRO_BODY(logger, logEvent, FATAL_LOG_LEVEL)

#define LOG4CPLUS_FATAL_STR(logger, logEvent)                           \
    LOG4CPLUS_MACRO_STR_BODY(logger, logEvent, FATAL_LOG_LEVEL)

#define LOG4CPLUS_FATAL_FMT(logger, logFmt, ...)                            \
    LOG4CPLUS_MACRO_FMT_BODY(logger, FATAL_LOG_LEVEL, logFmt, __VA_ARGS__)

#else
#define LOG4CPLUS_FATAL(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_FATAL_STR(logger, logEvent) LOG4CPLUS_DOWHILE_NOTHING()
#define LOG4CPLUS_FATAL_FMT(logger, logFmt, ...) LOG4CPLUS_DOWHILE_NOTHING()

#endif


//!If the condition given in second parameter evaluates false, this
//!macro logs it using FATAL log level, including the condition's
//!source text.
#define LOG4CPLUS_ASSERT(logger, condition)                             \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        if(!!(!(condition)))											\
            LOG4CPLUS_FATAL_STR((logger), "failed condition: "#condition)); \
    } while(0)                                                         \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()


#endif /* LOG4CPLUS_LOGGING_MACROS_HEADER_ */
