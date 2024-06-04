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
}
