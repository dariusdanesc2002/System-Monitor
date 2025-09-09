
#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <string>
#include <system.h>

#include "processor.h"

using namespace std;

class Display {
private:
    WINDOW* systemWindow = nullptr;
    WINDOW* processesWindow = nullptr;
    int scrollOffset = 0;

public:
    Display();
    ~Display();
    // his function will create the window, and will call the other functions
    // showSystem and showProcesses in order to update the window acordingly.
    void Run(System& system, Processor& processor);
    void increaseOffset();
    void decreaseOffset();
    int getOffset() const;
private:
    void showSystem(System& system, Processor& processor);
    void showProcesses(System& system);
    string progressBar(float percent);
};



#endif //DISPLAY_H
