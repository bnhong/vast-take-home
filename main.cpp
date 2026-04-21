#include <iostream>

#include "Simulation.h"

int main()
{
    Simulation simulation(5, 5);
    simulation.initialize();
    simulation.run();
    simulation.printSummary();

    std::cout<< "Simulation completed." << std::endl;
    
    return 0;
}