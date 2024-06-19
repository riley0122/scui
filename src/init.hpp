#pragma once

#ifndef SCUI_LOG_MODE
#define SCUI_LOG_MODE scui::LogMode::BAD
#endif

#if defined(_WIN32)
    #define PLATFORM "Windows"
    #include <windows.h>
#elif defined(__APPLE__)
    #define PLATFORM "Mac"
#elif defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(BSD)
    #define PLATFORM "BSD"
#else
    #define PLATFORM "Unknown"
#endif

#include <string>

namespace scui
{
    #ifdef _WIN32
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    #endif

    namespace {
        std::wstring stringToWideString(const std::string& str) {
            std::wstring wstr(str.begin(), str.end());
            return wstr;
        }

        const wchar_t* wideStringToCWcharArray(const std::wstring& wideString) {
            return wideString.c_str();
        }
    }

    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        // _ERROR instead of ERROR because ERROR is defined as 0 in windows.h
        _ERROR,
        FATAL
    };

    enum class LogMode {
        NONE,
        BAD,
        // _ERROR instead of ERROR because ERROR is defined as 0 in windows.h
        _ERROR,
        ALL
    };

    inline char* GetLogLevelString(LogLevel l) {
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
        case LogLevel::_ERROR:
            return "Error";
        case LogLevel::FATAL:
            return "Fatal";
        default:
            return "None";
        }
    }

    void log(std::string msg, LogLevel level);

    class Window {
    public:
        Window(std::string window_name);
        ~Window();

        bool Rename(std::string window_name);
        bool Resize(unsigned int w, unsigned h);
        bool Create(int w=-1, int h=-1);

    private:
        std::string window_name;
        unsigned int width;
        unsigned int height;

        #ifdef _WIN32
        bool WindowsCreate();
        #endif

        #ifdef __linux__
        bool LinuxCreate();
        #endif
    };
} // namespace scui
