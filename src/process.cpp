//
// Created by darius on 18.08.2025.
//

#include "process.h"
#include "linuxParser.h"

using namespace std;

void Process::setPid(int pid) {
    this->pid = pid;
}

void Process::setUser(int pid) {
    this->user = LinuxParser::User(pid);
}

void Process::setCommand(int pid) {
    this->command = LinuxParser::command(pid);
}
void Process::setRam(int pid) {
    this->RAM = LinuxParser::Ram(pid);
}

void Process::setUpTime(int pid, long int sysTime) {
    this->upTime = LinuxParser::upTime(pid, sysTime);
}

void Process::setCpuUtilization(int pid, long int sysTime) {
    this->CPU = LinuxParser::processCpuUtilization(pid, sysTime);
}

int Process::getPid() const {
    return this->pid;
}

string Process::getUser() const {
    return this->user;
}

string Process::getCommand() const {
    return this->command;
}
string Process::getRam() const {
    return this->RAM;
}

string Process::getUpTime() const {
    return this->upTime;
}

string Process::getCpuUtilization() const {
    return this->CPU;
}

bool Process::operator<(Process &process) const {

    return stol(this->getRam()) > stol(process.getRam());
}




