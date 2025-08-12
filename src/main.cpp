#include <iostream>
#include "display.h"
#include "linuxParser.h"

using namespace std;

int main() {
    // Display display;
    // display.Run();
    // vector<int> pids = LinuxParser::Pids();
    string number = LinuxParser::Uid(1);
    cout << number;
    return 0;
}
