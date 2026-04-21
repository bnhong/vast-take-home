#pragma once

#include <vector>

#include "Truck.h"
#include "Station.h"

constexpr int DEFAULT_SIMULATION_TIME = 72 * 60;

class Simulation {
public:
    Simulation(int numOfTrucks, int numOfStations, int totalMinutes = DEFAULT_SIMULATION_TIME, int seed = -1);

    void initialize();
    void run();
    void printSummary() const;

private:
    void tick(); // simulate one minute

    void updateTrucks();
    void updateStations();
    
    void processTruckArrivals();
    int generateMiningTimeInMinutes();

private:
    int m_numOfTrucks = 0;
    int m_numOfStations = 0;

    std::vector<Truck> m_trucks;
    std::vector<Station> m_stations;

    int m_totalMinutes = 0;
    int m_currentMinute = 0;
};