#ifndef TEA_CORE_LOGGER_H
#define TEA_CORE_LOGGER_H

#include <string>
#include <vector>

namespace tea {

#define LOG(logger, level, message) \
    logger->log(LogSource::CPlusPlus, \
                LogLevel::level, \
                std::string(__FILE_NAME__ " @ " + std::to_string(__LINE__) + ": ") + message)

enum class LogSource {
    CPlusPlus,
    Wren
};

enum class LogLevel {
    Info,
    Warn,
    Error,
    Debug,
    Trace
};

struct Log {
    LogSource source;
    LogLevel type;
    const std::string message;
};

class Logger {
public:
    Logger();

    void log(LogSource source, LogLevel level, const std::string& message);

    void set_max_log_level_from_cpp(LogLevel new_max);
    void set_max_log_level_from_wren(LogLevel new_max);
    void set_cpp_logging_allowed(bool allowed);
    void set_wren_logging_allowed(bool allowed);
protected:
    LogLevel max_level_from_cpp;
    LogLevel max_level_from_wren;
    bool cpp_logging_allowed;
    bool wren_logging_allowed;
    std::vector<Log> logs;
};

}

#endif // TEA_CORE_LOGGER_H