#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "secret.hpp"

using std::string;

// Hide user input
void stdio_echo(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if(enable)
        tty.c_lflag |= ECHO;
    else
        tty.c_lflag &= ~ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

string secret() {
    std::cout << "Hello and welcome! Input your token: ";
    string token;
    stdio_echo(false);
    std::getline(std::cin, token);
    stdio_echo(false);
    std::cout << std::endl;
    return token;
}