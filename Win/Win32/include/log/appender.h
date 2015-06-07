// -*- C++ -*-
// Module:  Log4CPLUS
// File:    appender.h


/** @file */

#ifndef LOG4CPLUS_APPENDER_HEADER_
#define LOG4CPLUS_APPENDER_HEADER_

#include "platform.h"

#include "layout.h"
#include "loglevel.h"

#include "pointer.h"
#include "filter.h"

#include <memory>


namespace log4cplus {

    class Properties;

    /**
     * This class is used to "handle" errors encountered in an {@link
     * Appender}.
     */
    class LOG4CPLUS_EXPORT ErrorHandler
    {
    public:
        ErrorHandler ();
        virtual ~ErrorHandler() = 0;
        virtual void error(const std::string& err) = 0;
        virtual void reset() = 0;
    };


    class LOG4CPLUS_EXPORT OnlyOnceErrorHandler : public ErrorHandler
    {
    public:
      // Ctor
        OnlyOnceErrorHandler();
        virtual ~OnlyOnceErrorHandler ();
        virtual void error(const std::string& err);
        virtual void reset();

    private:
        bool firstTime;
    };


    /**
     * Extend this class for implementing your own strategies for printing log
     * statements.
     *
     * <h3>Properties</h3>
     * <dl>
     *
     * <dt><tt>layout</tt></dt>
     * <dd>This property specifies message layout used by
     * Appender.
     * \sa Layout
     * </dd>
     *
     * <dt><tt>filters</tt></dt>
     * <dd>This property specifies possibly multiple filters used by
     * Appender. Each of multple filters and its properties is under a
     * numbered subkey of filters key. E.g.:
     * <tt>filters.<em>1</em>=LogLevelMatchFilter</tt>. Filter
     * subkey numbers must be consecutive.</dd>
     *
     * <dt><tt>Threshold</tt></dt>
     * <dd>This property specifies log level threshold. Events with
     * lower log level than the threshold will not be logged by
     * appender.</dd>
     *
     * <dt><tt>UseLockFile</tt></dt>
     * <dd>Set this property to <tt>true</tt> if you want your output
     * through this appender to be synchronized between multiple
     * processes. When this property is set to true then log4cplus
     * uses OS specific facilities (e.g., <code>lockf()</code>) to
     * provide inter-process locking. With the exception of
     * FileAppender and its derived classes, it is also necessary to
     * provide path to a lock file using the <tt>LockFile</tt>
     * property.
     * \sa FileAppender
     * </dd>
     *
     * <dt><tt>LockFile</tt></dt>
     * <dd>This property specifies lock file, file used for
     * inter-process synchronization of log file access. The property
     * is only used when <tt>UseLockFile</tt> is set to true. Then it
     * is mandatory.
     * \sa FileAppender
     * </dd>
     * </dl>
     */
    class LOG4CPLUS_EXPORT Appender : public virtual SharedObject
    {
    public:
      // Ctor
        Appender();
        Appender(const Properties & properties);

      // Dtor
        virtual ~Appender();

        /**
         * This function is for derived appenders to call from their
         * destructors. All classes derived from `Appender` class
         * _must_ call this function from their destructors. 
         * destroyed.
         */
        void destructorImpl();

      // Methods
        /**
         * Release any resources allocated within the appender such as file
         * handles, network connections, etc.
         * 
         * It is a programming errorto append to a closed appender.
         */
        virtual void close() = 0;

        /**
         * Check if this appender is in closed state.
         */
        bool isClosed() const;

        /**
         * This method performs threshold checks and invokes filters before
         * delegating actual logging to the subclasses specific {@link
         * #append} method.
         */
        void doAppend(const InternalLoggingEvent& loggingEvent);

        /**
         * Get the name of this appender. The name uniquely identifies the
         * appender.
         */
        virtual std::string getName();

        /**
         * Set the name of this appender. The name is used by other
         * components to identify this appender.
         */
        virtual void setName(const std::string& name);

        /**
         * Set the {@link ErrorHandler} for this Appender.
         */
        virtual void setErrorHandler(std::auto_ptr<ErrorHandler> eh);

        /**
         * Return the currently set {@link ErrorHandler} for this
         * Appender.
         */
        virtual ErrorHandler* getErrorHandler();

        /**
         * Set the layout for this appender. Note that some appenders have
         * their own (fixed) layouts or do not use one. For example, the
         * SocketAppender ignores the layout set here.
         */
        virtual void setLayout(std::auto_ptr<Layout> layout);

        /**
         * Returns the layout of this appender. The value may be NULL.
         * 
         * This class owns the returned pointer.
         */
        virtual Layout* getLayout();

        /**
         * Set the filter chain on this Appender.
         */
        void setFilter(FilterPtr f) { _filter = f; }

        /**
         * Get the filter chain on this Appender.
         */
        FilterPtr getFilter() const { return _filter; }

        /**
         * Returns this appenders threshold LogLevel. See the {@link
         * #setThreshold} method for the meaning of this option.
         */
        LogLevel getThreshold() const { return _threshold; }

        /**
         * Set the threshold LogLevel. All log events with lower LogLevel
         * than the threshold LogLevel are ignored by the appender.
         * 
         * In configuration files this option is specified by setting the
         * value of the <b>Threshold</b> option to a LogLevel
         * std::string, such as "DEBUG", "INFO" and so on.
         */
        void setThreshold(LogLevel th) { _threshold = th; }

        /**
         * Check whether the message LogLevel is below the appender's
         * threshold. If there is no threshold set, then the return value is
         * always <code>true</code>.
         */
        bool isAsSevereAsThreshold(LogLevel ll) const 
		{
            return ((ll != NOT_SET_LOG_LEVEL) && (ll >= _threshold));
        }

    protected:
      // Methods
        /**
         * Subclasses of <code>Appender</code> should implement this
         * method to perform actual logging.
         * @see doAppend method.
         */
        virtual void append(const InternalLoggingEvent& loggingEvent) = 0;


      // Data
        /** The layout variable does not need to be set if the appender
         *  implementation has its own layout. */
        std::auto_ptr<Layout> _layout;

        /** Appenders are named. */
        std::string _name;

        /** There is no LogLevel threshold filtering by default.  */
        LogLevel _threshold;

        /** The first filter in the filter chain. Set to <code>null</code>
         *  initially. */
        FilterPtr _filter;

        /** It is assumed and enforced that errorHandler is never null. */
        std::auto_ptr<ErrorHandler> _errorHandler;

        /** Is this appender closed? */
        bool _isClosed;
    };

    /** This is a pointer to an Appender. */
    typedef SharedObjectPtr<Appender> SharedAppenderPtr;

} // end namespace log4cplus

#endif // LOG4CPLUS_APPENDER_HEADER_

