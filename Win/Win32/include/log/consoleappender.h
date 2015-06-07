// -*- C++ -*-
// Module:  Log4CPLUS
// File:    consoleappender.h

/** @file */

#ifndef LOG4CPLUS_CONSOLE_APPENDER_HEADER_
#define LOG4CPLUS_CONSOLE_APPENDER_HEADER_

#include "platform.h"
#include "appender.h"
#include "thread/Mutex.h"

namespace log4cplus {
    /**
     * ConsoleAppender appends log events to <code>std::cout</code> or
     * <code>std::cerr</code> using a layout specified by the
     * user. The default target is <code>std::cout</code>.
     *
     * <h3>Properties</h3>
     * <dl>
     * <dt><tt>logToStdErr</tt></dt>
     * <dd>When it is set true, the output stream will be
     * <code>std::cerr</code> instead of <code>std::cout</code>.</dd>
     *
     * <dt><tt>ImmediateFlush</tt></dt>
     * <dd>When it is set true, output stream will be flushed after
     * each appended loggingEvent.</dd>
     * 
     * </dl>
     * \sa Appender
     */
    class LOG4CPLUS_EXPORT ConsoleAppender : public Appender {
    public:
      // Ctors
        ConsoleAppender(bool immediateFlush = false);
        ConsoleAppender(const Properties & properties);

      // Dtor
        ~ConsoleAppender();

      // Methods
        virtual void close();

        //!This mutex is used by ConsoleAppender and LogLog
        //!classes to synchronize output to console.
        static Mutex const& getOutputMutex();

    protected:
        virtual void append(const InternalLoggingEvent& loggingEvent);

      // Data
        /**
         * Immediate flush means that the underlying output stream
         * will be flushed at the end of each append operation.
         */
        bool _immediateFlush;
    };

} // end namespace log4cplus

#endif // LOG4CPLUS_CONSOLE_APPENDER_HEADER_

