//
// Created by darius on 18.08.2025.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using namespace std;

class Process {
public:
    void setPid(int pid);
    void setUser(int pid);
    void setCommand(int pid);
    void setCpuUtilization(int pid, long int sysTime);
    void setRam(int pid);
    void setUpTime(int pid, long int sysTime);

    int getPid() const;
    string getCpuUtilization() const;
    string getUser() const;
    string getCommand() const;
    string getRam() const;
    string getUpTime() const;

private:
    int pid = 0;
    string CPU;
    string upTime;
    string user;
    string command;
    string RAM;


};

#endif //PROCESS_H
