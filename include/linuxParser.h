//
// Created by darius on 05.08.2025.
//

#ifndef LINUXPARSER_H
#define LINUXPARSER_H

#include <string>
#include <vector>


using namespace std;

namespace LinuxParser {
    // Paths
    const string kProcDirectory{"/proc/"};
    const string kCmdlineFilename{"/cmdline"};
    const string kCpuinfoFilename{"/cpuinfo"};
    const string kStatusFilename{"/status"};
    const string kStatFilename{"/stat"};
    const string kUptimeFilename{"/uptime"};
    const string kMeminfoFilename{"/meminfo"};
    const string kVersionFilename{"/version"};
    const string kOSPath{"/etc/os-release"};
    const string kPasswordPath{"/etc/passwd"};

    // System
    float memoryUtilization();
    string upTime();
    int totalProcesses();
    int runningProcesses();
    string operatingSystem();
    string Kernel();

    // Processes
    vector<int> Pids();
    std::string Command(int pid);
    std::string Ram(int pid);
    string Uid(int pid);
    std::string User(int pid);
    long int UpTime(int pid);

    // CPU
    enum CPUStates {
        kUser_ = 0,
        kNice_,
        kSystem_,
        kIdle_,
        kIOwait_,
        kIRQ_,
        kSoftIRQ_,
        kSteal_,
        kGuest_,
        kGuestNice_
      };
    // Processor
    std::vector<std::string> CpuUtilization();
    long Jiffies();
    long ActiveJiffies();
    long ActiveJiffies(int pid);
    long IdleJiffies();

};



#endif //LINUXPARSER_H
