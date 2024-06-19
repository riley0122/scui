#include "../scui.hpp"
#include "test_lib.hpp"

bool testCreatingWindow() {
    scui::Window w("Hello, World!");
    return w.Create(100, 100);
}

int main() {
    return run_tests({
        testCreatingWindow()
    },{
        "Create window"
    });
}
