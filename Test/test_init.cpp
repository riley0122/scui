#include "../src/init.hpp"
#include "test_lib.hpp"

bool testGettingLevelName() {
    return scui::GetLogLevelString(scui::LogLevel::FATAL) == "Fatal" &&
           scui::GetLogLevelString(scui::LogLevel::_ERROR) == "Error" &&
           scui::GetLogLevelString(scui::LogLevel::WARN) == "Warn" &&
           scui::GetLogLevelString(scui::LogLevel::INFO) == "Info" &&
           scui::GetLogLevelString(scui::LogLevel::DEBUG) == "Debug" &&
           scui::GetLogLevelString(scui::LogLevel::TRACE) == "Trace";
}

int main() {
    return run_tests({
        testGettingLevelName()
    },{
        "Get log level name"
    });
}
