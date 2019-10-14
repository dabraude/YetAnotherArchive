/** Copyright David Braude 2019 */
#ifndef SRC_LOG_HPP_
#define SRC_LOG_HPP_

#include <map>

#include <string>

#ifndef YAA_DEFAULT_LOG_LEVEL
#define YAA_DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

namespace YAA {

enum LOG_LEVEL {
    LOG_LEVEL_CRITICAL = 50,
    LOG_LEVEL_ERROR = 40,
    LOG_LEVEL_WARN = 30,
    LOG_LEVEL_INFO = 20,
    LOG_LEVEL_DEBUG = 10
};

class Log
{
    /* overly simple log, to be replaced with your logging system
     */
public:

    Log();

    /** Log a message at the given level */
    void log(enum LOG_LEVEL level, const std::string& message);

    /** Log a critical message */
    void critical(const std::string& message);

    /** Log an error message */
    void error(const std::string& message);

    /** Log a warning message */
    void warn(const std::string& message);

    /** Log an info message */
    void info(const std::string& message);

    /** Log a debug message */
    void debug(const std::string& message);

    /** Check if the logger has been enabled for the given level
     *
     * @param level the log level to test against
     * @returns true if it has 
     */
    bool is_enabled_for(enum LOG_LEVEL level);


    /** Enable the logger for the given level
     *
     * @param level the level to enable for
     */
    void enable_for(enum LOG_LEVEL level);

protected:
    enum LOG_LEVEL _level = YAA_DEFAULT_LOG_LEVEL;
    static std::map<int, std::string> _level_names;
};



}

#endif // SRC_HEADER_HPP_