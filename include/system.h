//
// Created by darius on 13.08.2025.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <processor.h>
#include <string>

using namespace std;
class System {
public:
    // Processor& CPU ();
    void setKernel();
    void setOperatingSystem();
    void setUpTime();
    void setMemoryUtilization();
    void setTotalProcesses();
    void setRunningProcesse();
    long getUpTime() const;
    float getMem() const;
    int getTotalProcesses() const;
    int getRunningProcesses() const;
    string getKernel() const;
    string getOperatingSystem() const;
    string getUpTimeString() const;


private:
    long upTime = 0;
    float Mem = 0;
    int totalProcesses = 0;
    int runningProcesses = 0;
    string Kernel;
    string OperatingSystem;
    string upTimeString;
};







#endif //SYSTEM_H
;