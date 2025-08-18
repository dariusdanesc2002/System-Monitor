//
// Created by darius on 14.08.2025.
//

#include "processor.h"
#include "linuxParser.h"

void Processor::setUsageCPU() {
    double usgae = LinuxParser::cpuUtilization();
    this->usageCPU = usgae;
}

double Processor::getUsageCPU() const {
    return this->usageCPU;
}




