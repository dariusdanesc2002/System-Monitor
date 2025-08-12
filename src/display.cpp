// #include "../include/display.h"
#include "display.h"
// In ncurses y represents the lines and x represents the cols
#include "linuxParser.h"

using namespace std;

Display::Display() {

    initscr();
    cbreak();
    noecho();
    start_color();
    curs_set(0);

    const int xMaxScreen = getmaxx(stdscr); // get the total no. of screen cols
    this->systemWindow = newwin(10, xMaxScreen, 0, 0);
    // this->processesWindow = newwin(n, xMaxScreen, 0, 0); // n = no. of process
    this->processesWindow = newwin(10, xMaxScreen, systemWindow->_maxy + 1, 0);
    nodelay(systemWindow, TRUE);
    nodelay(processesWindow, TRUE);
}

Display::~Display() {
    delwin(systemWindow);
    delwin(processesWindow);
    endwin();
}


void Display::Run() {


    // this while will run until the user press ctrl + c
    while (1) {

        char ch = wgetch(systemWindow);
        if (ch == 'q')
            break;

        box(systemWindow, 0, 0);
        box(processesWindow, 0, 0);
        showSystem();
        showProcesses();
        delay_output(120); // delay 100 ms
        wnoutrefresh(systemWindow);   // Refresh the virtual screen
        wnoutrefresh(processesWindow); // Refresh the virtual screen

        doupdate(); // Update the physical screen once
    }

}

string Display::progressBar(float percent) {
    int size = 50;
    float bars = percent * size;
    string result = "%0";

    for (int i = 0; i < size; i++) {
        if (i <= bars) {
            result += '|';
        }
        else {
            result += ' ';
        }
    }
    string display = to_string(percent * 100).substr(0, 4);
    if (percent < 0.1 || percent == 1.0)
        display = " " + to_string(percent * 100).substr(0, 3);

    return result + " " + display + "/100%";

}


void Display::showSystem() {
    int row = 0;
    mvwprintw(systemWindow, ++row, 2, "%s", ("OS: " + LinuxParser::operatingSystem()).c_str());
    mvwprintw(systemWindow, ++row, 2, "%s", ("Kernel: " + LinuxParser::Kernel()).c_str());
    mvwprintw(systemWindow, ++row, 2, "CPU: ");
    // wattron(systemWindow, COLOR_PAIR(1));
    mvwprintw(systemWindow, row, 10, "%s", "");
    wprintw(systemWindow, "%s", progressBar(0.20).c_str());
    // wattroff(systemWindow, COLOR_PAIR(1));
    mvwprintw(systemWindow, ++row, 2, "Memory: ");
    // wattron(systemWindow, COLOR_PAIR(1));
    mvwprintw(systemWindow, row, 10, "%s", "");
    wprintw(systemWindow, "%s", progressBar(LinuxParser::memoryUtilization()).c_str());
    // wattroff(systemWindow, COLOR_PAIR(1));
    mvwprintw(systemWindow, ++row, 2, "%s", ("Total Processes: " + to_string(LinuxParser::totalProcesses())).c_str());
    mvwprintw(systemWindow, ++row, 2, "%s", ("Running Processes: " + to_string(LinuxParser::runningProcesses())).c_str());
    mvwprintw(systemWindow, ++row, 2, "%s", ("Up Time: " + LinuxParser::upTime()).c_str());
    wrefresh(systemWindow);
}

void Display::showProcesses() {
    vector<int> pids = LinuxParser::Pids();
    int row = 0;
    int n = 7;
    int const pid_column = 2;
    int const user_column = 9;
    int const cpu_column = 16;
    int const ram_column = 26;
    int const time_column = 35;
    int const command_column = 46;
    // wattron(window, COLOR_PAIR(2));
    mvwprintw(processesWindow, ++row, pid_column, "PID");
    mvwprintw(processesWindow, row, user_column, "USER");
    mvwprintw(processesWindow, row, cpu_column, "CPU[%%]");
    mvwprintw(processesWindow, row, ram_column, "RAM[MB]");
    mvwprintw(processesWindow, row, time_column, "TIME+");
    mvwprintw(processesWindow, row, command_column, "COMMAND");
    // wattroff(window, COLOR_PAIR(2));
    for (int i = 0; i < n; ++i) {
        //You need to take care of the fact that the cpu utilization has already been multiplied by 100.
        // Clear the line
        mvwprintw(processesWindow, ++row, pid_column, (string(processesWindow->_maxx-2, ' ').c_str()));

        mvwprintw(processesWindow, row, pid_column, "%s", to_string(pids[i]).c_str());
        // mvwprintw(systemWindow, row, user_column, "%s", processes[i].User().c_str());
        float cpu = 0.1 * 100;
        mvwprintw(processesWindow, row, cpu_column, "%s", to_string(cpu).substr(0, 4).c_str());
        // mvwprintw(systemWindow, row, ram_column, "%s", processes[i].Ram().c_str());
        // mvwprintw(systemWindow, row, time_column, "%s",
        //           Format::ElapsedTime(processes[i].UpTime()).c_str());
        // mvwprintw(systemWindow, row, command_column, "%s",processes[i].Command().substr(0, systemWindow->_maxx - 46).c_str());
    }
}






