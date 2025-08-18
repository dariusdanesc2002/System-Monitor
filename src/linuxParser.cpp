#include "linuxParser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip> // for setw and setfill
#include <cmath>
#include <filesystem>
#include <unistd.h>
#include <system.h>
#include <unistd.h>

using namespace std;

// SYSTEM

string LinuxParser::operatingSystem() {
    ifstream stream{kOSPath};
    string line{};
    string name{}; // EX: PRETTY_NAME/NAME/VERSION_CODENAME/ etc..
    string key{}; // EX: Ubuntu 22.04.5 LTS/jammy/ etc...

    if (!stream) {
        printf("The file %s could not be opened!\n", kOSPath.c_str());
        return {};
    }else {
        while(getline(stream, line)) {
            replace(line.begin(), line.end(), ' ','_');
            replace(line.begin(), line.end(), '=', ' ');
            replace(line.begin(), line.end(), '"', ' ');

            istringstream lineStream (line);
            while (lineStream >> name >> key) {
                if(name == "PRETTY_NAME") {
                    replace(key.begin(), key.end(), '_',' ');
                    return key;
                }
            }
        }
    }
    return {};
}

string LinuxParser::Kernel() {
    ifstream stream{kProcDirectory + kVersionFilename};
    string line{};
    string linux{};
    string version{};
    string number{};

    if(!stream) {
        printf("The file %s could not be opened!\n", (kProcDirectory + kVersionFilename).c_str());
        return {};
    }else {
        getline(stream, line);
        istringstream lineStream (line);
        lineStream >> linux >> version >> number;
        return number;
    }
}

int LinuxParser::totalProcesses() {
    ifstream stream(kProcDirectory + kStatFilename);
    string line{};
    string name{};
    int number = 0;
    if(!stream) {
        printf("The file %s could not be opened \n", (kProcDirectory + kStatFilename).c_str());
        return 0;
    }else {
        while (getline(stream, line) ){
            istringstream lineStream (line);
            while (lineStream  >> name >> number) {
                if (name == "processes") {
                    return number;
                }
            }
        }
    }
    return number;
}

int LinuxParser::runningProcesses() {
    ifstream stream(kProcDirectory + kStatFilename);
    string line{};
    string name{};
    int number = 0;
    if (!stream) {
        printf("The file %s could not be opened \n", (kProcDirectory + kStatFilename).c_str());
        return 0;
    }else {
        while (getline(stream, line)) {
            istringstream lineStream(line);
            while (lineStream >> name >> number) {
                if (name == "procs_running") {
                    return number;
                }
            }
        }
    }
    return number;
}

void LinuxParser::upTime(long& upTime, string& upTimeString) {
    ifstream stream(kProcDirectory + kUptimeFilename);
    string line{};
    string hours{};
    string minutes{};
    string seconds{};
    string result{};

    long sysUptime;
    long idleUptime;

    if (!stream) {
        printf("The file %s could not be opened", (kProcDirectory + kUptimeFilename).c_str());
        return ;
    }else {
        while (getline(stream, line)) {
            istringstream lineStream(line);
            lineStream >> sysUptime >> idleUptime;
        }

        hours = to_string(sysUptime / 3600);
        minutes = to_string((sysUptime % 3600) / 60);
        seconds = to_string(((sysUptime % 3600) % 60));

        stringstream timeStream;
        timeStream << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
        upTime = sysUptime;
        upTimeString = timeStream.str();
    }
}

float LinuxParser::memoryUtilization() {
    ifstream stream(kProcDirectory + kMeminfoFilename);
    string line{};
    string name;
    float mem;
    float MemTotal{};
    float MemFree{};

    if (!stream) {
        printf("The file %s could not be opened", (kProcDirectory + kMeminfoFilename).c_str());
        return 0;
    }else {
        while (getline(stream, line)) {
            istringstream lineStream(line);

            while (lineStream >> name >> mem) {
                if (name == "MemTotal:") {
                    MemTotal = mem;
                }
                if (name == "MemFree:") {
                    MemFree = mem;
                    break;
                }
            }
            if (MemFree != 0)
                break;
        }
        float percent = trunc((100 * (MemTotal - MemFree) )/ MemTotal * 100);
        return percent / 10000; // returns the percent ex 0.21
    }

}

// PROCESS

vector<int> LinuxParser::Pids() {
    filesystem::path filePath = kProcDirectory;
    vector<int> pids;
    try {
        if (!filesystem::is_directory(filePath)) {
            scanf("The path could not be opened");
            return pids;
        }

        for (const auto& dir_path: filesystem::directory_iterator(filePath)) {
            if (dir_path.is_directory()) {
                string fileName = dir_path.path().filename().string();
                if (!fileName.empty() && all_of(fileName.begin(), fileName.end(), ::isdigit)) {
                    pids.push_back(stoi(fileName));
                }
            }
        }
    }catch (const filesystem::filesystem_error& error){}

    return pids;
}

string LinuxParser::Uid(int pid) {
    ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
    string key{};
    string line{};
    string number  = "-1";

    if (!stream) {
        printf("The file %s could not be opened", (kProcDirectory + to_string(pid) + kStatFilename).c_str());
        return number;
    }

    while (getline(stream, line)) {
        istringstream lineStream(line);
        while (lineStream >> key >> number) {
            if (key == "Uid:") {
                return number;
            }
        }

    }
    return number;

}

string LinuxParser::User(int pid) {
    ifstream stream(kPasswordPath);
    string line{};
    string number{};
    string username{};
    string uid = LinuxParser::Uid(pid);
    if (!stream) {
        printf("The file %s could not be opened ", (kPasswordPath).c_str());
    }
    while (getline(stream, line)) {
        replace(line.begin(), line.end(), ':',' ');
        replace(line.begin(), line.end(), 'x',' ');
        istringstream lineStream(line);
        while (lineStream >> username >> number) {
            if (number == uid)
                return username;
        }
    }

    return username;
}

string LinuxParser::Ram(int pid) {
    ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
    string line{};
    string key;
    int value;
    if (!stream) {
        printf("The file %s could not be opened ", (kProcDirectory + to_string(pid) + kStatusFilename).c_str());
    }

    while (getline(stream, line)) {
        istringstream lineStream(line);
        while (lineStream >> key >> value) {
            if (key == "Kthread:" && value == 1) {
                return "[0]";
            }
            if (key == "VmSize:") {
                value = value  / 1024; // transform from KB to MB
                return to_string(value);
            }
        }
    }
    return {};
}

string LinuxParser::upTime(int pid, long int sysUpTime) {
    ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
    string line{};
    string key{};

    if (!stream) {
        printf("The file %s could not be opened ", (kProcDirectory + to_string(pid) + kStatFilename).c_str());
        return key;
    }

    while (getline(stream, line)) {
        istringstream lineStream(line);
        for (int i = 0; i < 21; i++) {
            lineStream >> key;
        }
        lineStream >> key;
    }
    // DE REVIZUIT LOGICA DUPA IMPLEMENTAREA CLASELOR
    long clockTick = stol(key);
    clockTick = clockTick / sysconf(_SC_CLK_TCK);
    long processUpTime = sysUpTime - clockTick;
    string hours{};
    string minutes{};
    string seconds{};
    hours = to_string(processUpTime / 3600);
    minutes = to_string((processUpTime % 3600) / 60);
    seconds = to_string(((processUpTime % 3600) % 60));

    stringstream timeStream;
    timeStream << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
    // cout << timeStream.str() << endl;
    return timeStream.str();

}

string LinuxParser::command(int pid) {
    ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
    string line;
    if (!stream) {
        printf("The file %s could not be opened ", (kProcDirectory + to_string(pid) + kCmdlineFilename).c_str());
        return {};
    }
    getline(stream, line);
    return line;

}

string LinuxParser::processCpuUtilization(int pid, long int sysUpTime) {
    ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
    string line{};
    string utime, stime, cutime, cstime;
    long starttime;
    string number;
    if (!stream) {
        printf("The file %s could not be opened", (kProcDirectory + to_string(pid) + kStatFilename).c_str());
        return "0%";
    }
    getline(stream, line);
    istringstream streamLine(line);
    for (int i = 1; i < 22; i++) {
        streamLine >> number;
        if (i == 14)
            utime = number;
        if (i == 15)
            stime = number;
        if (i == 16)
            cutime = number;
        if (i == 17)
            cstime = number;
    }
    streamLine >> starttime;
    long total_time = stol(utime) + stol(stime) + stol(cutime) + stol(cstime);
    total_time /= sysconf(_SC_CLK_TCK);
    starttime /= sysconf(_SC_CLK_TCK);
    long seconds = sysUpTime - starttime;
    double cpuUsage = (static_cast<double>(total_time) / seconds);

    return to_string(cpuUsage) + "%";
}

pair<double, double> LinuxParser::cpuSnapshot() {
    ifstream stream(kProcDirectory + kStatFilename);
    string line{};
    string cpu;
    double number;
    vector<double> values(10,0);
    pair<double, double> snapshot;
    if (!stream) {
        printf("the file %s could not be openead", (kProcDirectory + kStatFilename).c_str());
        return snapshot;
    }
    getline(stream, line);
    istringstream streamLine(line);
    streamLine >> cpu;

    for (int i = 0; i < 10; i++) {
        streamLine >> number;
        values[i] = number;
    }

    double idleTime;
    double activeTIme;
    double totalTime;

    activeTIme = values[0] + values[1] + values[2] + values[5] + values[6] + values[7]; // user + nice + system + irq + softirq + steal
    idleTime = values[3] + values[4]; // iowait + idle
    totalTime = idleTime + activeTIme;
    snapshot.first = activeTIme;
    snapshot.second = totalTime;

    return snapshot;

}

double LinuxParser::cpuUtilization() {
    pair<double, double> snapshot1 = LinuxParser::cpuSnapshot();
    sleep(1);
    pair<double, double> snapshot2 = LinuxParser::cpuSnapshot();

    return (snapshot2.first - snapshot1.first)/(snapshot2.second - snapshot1.second);
}















