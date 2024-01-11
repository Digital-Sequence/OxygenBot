#include "catch_exit_signal.hpp"
#include <signal.h>

bool isRunning = true;

void catch_exit_signal() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = [](int c) {
        isRunning = false;
    };
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    while(isRunning) {
        sigaction(SIGINT, &sigIntHandler, 0);
    }
}