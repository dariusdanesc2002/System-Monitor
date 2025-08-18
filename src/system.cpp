//
// Created by darius on 13.08.2025.
//

#include "system.h"
#include "linuxParser.h"


void System::setKernel() {

    this->Kernel = LinuxParser::Kernel();
}

void System::setOperatingSystem() {
    this->OperatingSystem = LinuxParser::operatingSystem();
}

void System::setMemoryUtilization() {
    this->Mem = LinuxParser::memoryUtilization();
}


void System::setUpTime() {
    LinuxParser::upTime(this->upTime, this->upTimeString);
}

void System::setTotalProcesses() {
    this->totalProcesses = LinuxParser::totalProcesses();
}

void System::setRunningProcesse() {
    this->runningProcesses = LinuxParser::runningProcesses();
}


string System::getKernel() const {
    return this->Kernel;
}

string System::getOperatingSystem() const {
    return this->OperatingSystem;
}

float System::getMem() const {
    return Mem;
}


long System::getUpTime() const {

    return this->upTime;
}

int System::getTotalProcesses() const {
    return this->totalProcesses;
}

int System::getRunningProcesses() const {
    return this->runningProcesses;
}

string System::getUpTimeString() const {
    return this->upTimeString;
}





