#include "../process_scheduling/processes_sim.hpp"

Processes::Processes(std::string filepath){
    Process paux;
    std::ifstream file;
    file.open(filepath);
    while(file >> paux.pId >> paux.cpuPeak){
        paux.waitedTime = 0;
        plist.push_back(paux);
    }
}

void Processes::FCFS(){
    std::list<Process> copyList (plist.begin(), plist.end());
    int avr_waited_time = 0;
    int waited_time = 0;
    std::ofstream fcfs_times;
    fcfs_times.open("fcfs_waited_times.dat");

    for(std::list<Process>::iterator it = copyList.begin(); it != copyList.end(); it++){
        avr_waited_time += waited_time;
        fcfs_times << it->pId << " " << waited_time << std::endl;
        it->waitedTime = waited_time; 
        waited_time += it->cpuPeak;
        it->cpuPeak = 0;
    }

    avr_waited_time = avr_waited_time/plist.size();
    fcfs_times << "average waited time " << avr_waited_time;
    fcfs_times.close();
}

void Processes::SJF(){
    std::list<Process> sortedList (plist.begin(), plist.end());
    sortedList.sort();

    int avr_waited_time = 0;
    int waited_time = 0;
    std::ofstream sjf_times;
    sjf_times.open("sjf_waited_times.dat");

    for(std::list<Process>::iterator it = sortedList.begin(); it != sortedList.end(); it++){
        avr_waited_time += waited_time;
        sjf_times << it->pId << " " << waited_time << std::endl;
        it->waitedTime = waited_time; 
        waited_time += it->cpuPeak;
        it->cpuPeak = 0;
    }

    avr_waited_time = avr_waited_time/plist.size();
    sjf_times << "average waited time " << avr_waited_time;
    sjf_times.close();
}

void Processes::roundRobin(int tq){
    std::list<Process> copyList (plist.begin(), plist.end());
    int avr_waited_time = 0;
    std::ofstream rr_times;
    rr_times.open("roundRobin"+std::to_string(tq)+"_waited_times.dat");

    while(!copyList.empty()){
        if(copyList.size()!=1){
            if(copyList.front().cpuPeak > tq){
                copyList.front().cpuPeak -= tq;
                for(std::list<Process>::iterator it = ++copyList.begin(); it != copyList.end(); it++){
                    it->waitedTime += tq;
                }
                copyList.push_back(copyList.front());
                copyList.pop_front();
            }

            if(copyList.front().cpuPeak <= tq){
                for(std::list<Process>::iterator it = ++copyList.begin(); it != copyList.end(); it++){
                    it->waitedTime += copyList.front().cpuPeak;
                }
                rr_times << copyList.front().pId << " " << copyList.front().waitedTime << std::endl;
                avr_waited_time += copyList.front().waitedTime;
                copyList.pop_front();
            }
        }else{
            rr_times << copyList.front().pId << " " << copyList.front().waitedTime << std::endl;
            avr_waited_time += copyList.front().waitedTime;
            copyList.pop_front();
        }
    }

    avr_waited_time = avr_waited_time/plist.size();
    rr_times << "average waited time " << avr_waited_time;
    rr_times.close();
}

void Processes::printCpuTimes(){
    for(std::list<Process>::iterator it = plist.begin(); it != plist.end(); it++){
        std::cout << it->cpuPeak << std::endl;
    }
}