#include <iostream>
#include "class.h"


using namespace std;
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void clearScreen() {
#ifdef _WIN32
    // Clear screen for Windows
    system("cls");
#else
    // Clear screen for other operating systems (Linux, macOS)
    std::cout << "\033[2J\033[H";
#endif
}

