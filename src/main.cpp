#include <iostream>
#include "display.h"
#include "linuxParser.h"
#include "processor.h"
#include "system.h"

using namespace std;

int main() {
    System system;
    Processor processor;
    Display display;
    display.Run(system, processor);
    // LinuxParser::upTime(system);
    // LinuxParser::upTime(11526, system);
    return 0;
}