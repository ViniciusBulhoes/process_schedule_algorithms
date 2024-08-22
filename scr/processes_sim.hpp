#ifndef PROCESSES_H
#define PROCESSES_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>

class Processes {
    public:
        struct Process {
            int pId;
            int cpuPeak;
            int waitedTime;
            bool operator<(Process const& c1)const{
                return this->cpuPeak < c1.cpuPeak;
            }
        };
        void FCFS();
        void SJF();
        void roundRobin(int tq);
        void printCpuTimes();
        Processes(std::string filepath);
        std::list<Process> plist;
};

#endif