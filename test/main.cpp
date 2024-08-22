#include "../process_scheduling/processes_sim.hpp"

int main(){
    Processes trab_so("../process_scheduling/picos_cpu.dat");
    
    //trab_so.printCpuTimes();
    trab_so.FCFS();
    trab_so.SJF();
    trab_so.roundRobin(10);
    trab_so.roundRobin(100);

    return 0;
}