#include "core/logger.h"

#include <iostream>

namespace tea {

Logger::Logger()
    : max_level_from_cpp(LogLevel::Trace), max_level_from_wren(LogLevel::Trace),
      cpp_logging_allowed(true), wren_logging_allowed(true)
    { }

void Logger::log(LogSource source, LogLevel level, const std::string& message) {
    bool should_not_log = (source == LogSource::CPlusPlus && level > max_level_from_cpp)
                          || (source == LogSource::Wren && level > max_level_from_wren)
                          || (source == LogSource::CPlusPlus && !cpp_logging_allowed)
                          || (source == LogSource::Wren && !wren_logging_allowed);
    if (should_not_log) {
        return;
    }

    const auto source_string = [source]() -> const char* {
        switch (source) {
        case LogSource::CPlusPlus: return "C++";
        case LogSource::Wren:  return "Wren";
        default: return "??";
        }
    }();

    const auto type_string = [level]() -> const char* {
        switch (level) {
        case LogLevel::Info:  return "info";
        case LogLevel::Warn:  return "warn";
        case LogLevel::Error: return "error";
        case LogLevel::Debug: return "debug";
        case LogLevel::Trace: return "trace";
        default: return "??";
        }
    }();

    std::cout << "[" << source_string << "] [" << type_string << "]\n" << message << "\n";

    Log log { source, level, message };
    logs.push_back(log);
}

void Logger::set_max_log_level_from_cpp(LogLevel new_max) {
    max_level_from_cpp = new_max;
}

void Logger::set_max_log_level_from_wren(LogLevel new_max) {
    max_level_from_wren = new_max;
}

void Logger::set_cpp_logging_allowed(bool allowed) {
    cpp_logging_allowed = allowed;
}

void Logger::set_wren_logging_allowed(bool allowed) {
    wren_logging_allowed = allowed;
}

}