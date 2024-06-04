#pragma once

#ifndef SCUI_LOG_MODE
#define SCUI_LOG_MODE scui::LogMode::BAD
#endif

#include <string>

namespace scui
{
    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    enum class LogMode {
        NONE,
        BAD,
        ERROR,
        ALL
    };

    char* GetLogLevelString(LogLevel l) {
        switch (l)
        {
        case LogLevel::TRACE:
            return "Trace";
        case LogLevel::DEBUG:
            return "Debug";
        case LogLevel::INFO:
            return "Info";
        case LogLevel::WARN:
            return "Warn";
        case LogLevel::ERROR:
            return "Error";
        case LogLevel::FATAL:
            return "Fatal";
        default:
            return "None";
        }
    }

    void log(std::string msg, LogLevel level);
} // namespace scui
