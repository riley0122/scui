#include "init.hpp"
#include <iostream>

namespace scui {
    void log(std::string msg, LogLevel level) {
        if (SCUI_LOG_MODE == LogMode::NONE)
            return;
        else if (SCUI_LOG_MODE == LogMode::ALL) {
            std::cout << "[scui] " << GetLogLevelString(level) << ": " << msg;
        }
    };

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg)
        {
        case WM_SIZE:
            log("Resize event called", LogLevel::TRACE);
            break;
        
        default:
            log("Some other event called", LogLevel::TRACE);
            break;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    Window::Window(std::string window_name) {
        if (PLATFORM == "Unknown") {
            log("Unknown operating system!", LogLevel::FATAL);
            exit(1);
        } else if (PLATFORM == "BSD" || PLATFORM == "Mac") {
            log("Your operating system is not yet supported by SCUI!", LogLevel::FATAL);
            exit(1);
        }

        this->window_name = window_name;
    }

    Window::~Window() {
        // TODO: Clean up.
    }

    bool Window::Rename(std::string window_name) {
        this->window_name = window_name;
        return true;
    }

    bool Window::Resize(unsigned int w, unsigned int h) {
        this->width = w;
        this->height = h;
        return true;
    }

    bool Window::Create(int w, int h) {
        unsigned int width;
        unsigned int height;

        if (w == -1)
            width = this->width;
        else
            Resize(w, this->height);

        if (h == -1)
            height = this->height;
        else
            Resize(this->height, h);

        #ifdef _WIN32
        return WindowsCreate();
        #endif

        return false;
    }

    #ifdef __linux__
    bool Window::LinuxCreate() {
        return false;
    }
    #endif

    #ifdef _WIN32
    bool Window::WindowsCreate() {
        // Initialize properties
        const LPCSTR CLASS_NAME = "SCUI window class";

        WNDCLASSA wc = { };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = CLASS_NAME;

        RegisterClassA(&wc);

        // const wchar_t* window_name = wideStringToCWcharArray(stringToWideString(this->window_name));

        // Create the window
        HWND hwnd = CreateWindowExA(
            0,
            CLASS_NAME,
            this->window_name.c_str(),
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,

            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
        );

        if (hwnd == NULL) {
            log("Failed to create window!", LogLevel::_ERROR);
            return false;
        }

        ShowWindow(hwnd, SW_SHOW);

        return true;
    }
    #endif
}
