#include "linuxParser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip> // for setw and setfill
#include <cmath>
#include <filesystem>
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

string LinuxParser::upTime() {
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
        return {};
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


        return timeStream.str();

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
    ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
    string key{};
    string line{};
    string number  = "-1";

    if (!stream) {
        printf("The file %s could not be oppend", (kProcDirectory + to_string(pid) + kStatFilename).c_str());
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








