//
// Created by darius on 14.08.2025.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <string>

using namespace std;

class Processor {
public:
    double getUsageCPU() const;
    void setUsageCPU();
private:

    double usageCPU = 0;
};

#endif //PROCESSOR_H
