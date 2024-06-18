#include "init.hpp"
#include <iostream>

#ifdef _WIN32
HINSTANCE g_hInstance;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    g_hInstance = hInstance;
}

void OnSize(HWND hwnd, UINT flag, int width, int height) {
    scui::log("Resize event called", scui::LogLevel::TRACE);
    // Handle resizing
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SIZE:
        {
            int width = LOWORD(lParam);  // Macro to get the low-order word.
            int height = HIWORD(lParam); // Macro to get the high-order word.

            // Respond to the message:
            OnSize(hwnd, (UINT)wParam, width, height);
        }
        break;
    }
}
#endif

namespace scui {
    void log(std::string msg, LogLevel level) {
        if (SCUI_LOG_MODE == LogMode::NONE)
            return;
        else if (SCUI_LOG_MODE == LogMode::ALL) {
            std::cout << "[scui] " << GetLogLevelString(level) << ": " << msg;
        }
    };

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

        if (PLATFORM == "Windows")
            return WindowsCreate();
        else if (PLATFORM == "Linux")
            return LinuxCreate();
    }

    bool Window::WindowsCreate() {
        const std::wstring wide = stringToWideString(this->window_name);
        const wchar_t* CLASS_NAME = wideStringToCWcharArray(wide);

        // Dont know if this will compile on linux because no windows.h
        // Need to check and possibly fix.
        WNDCLASS wc = {  };

        wc.lpfnWndProc   = WindowProc;
        wc.hInstance     = g_hInstance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);
    }
}
