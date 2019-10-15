
/** Copyright David Braude 2019 */

#include <iostream>

#include "Log.hpp"

namespace YAA {

std::map<int, std::string> Log::_level_names;


Log::Log() {
    if (!Log::_level_names.size()) {
        Log::_level_names[LOG_LEVEL_CRITICAL]    = "CRITICAL:";
        Log::_level_names[LOG_LEVEL_ERROR]       = "ERROR:   ";
        Log::_level_names[LOG_LEVEL_WARN]        = "WARN:    ";
        Log::_level_names[LOG_LEVEL_INFO]        = "INFO:    ";
        Log::_level_names[LOG_LEVEL_DEBUG]       = "DEBUG:   ";
    }
}

bool Log::is_enabled_for(enum LOG_LEVEL level)
{
    return _level <= level;
}


void Log::enable_for(enum LOG_LEVEL level)
{
    _level = level;
}

void Log::log(enum LOG_LEVEL level, const std::string& message)
{
    if (is_enabled_for(level))
        std::cerr << Log::_level_names[level] << " " << message << std::endl;
}

void Log::critical(const std::string& message)
{
    log(LOG_LEVEL_CRITICAL, message);
}

void Log::error(const std::string& message)
{
    log(LOG_LEVEL_ERROR, message);
}

void Log::warn(const std::string& message)
{
    log(LOG_LEVEL_WARN, message);
}

void Log::info(const std::string& message)
{
    log(LOG_LEVEL_INFO, message);
}

void Log::debug(const std::string& message)
{
    log(LOG_LEVEL_DEBUG, message);
}

}