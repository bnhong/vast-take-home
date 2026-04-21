#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Simulation.h"

namespace {
    constexpr int MIN_MINING_TIME_IN_MINUTES = 60;
    constexpr int MAX_MINING_TIME_IN_MINUTES = 300;
    constexpr int TRAVEL_TIME_IN_MINUTES     = 30;
    constexpr int UNLOAD_TIME_IN_MINUTES     = 5;
}

Simulation::Simulation(int numOfTrucks, int numOfStations, int totalMinutes, int seed)
    : m_numOfTrucks(numOfTrucks), 
      m_numOfStations(numOfStations), 
      m_totalMinutes(totalMinutes), 
      m_currentMinute(0)
{
    if (seed == -1) {
        std::srand(std::time(nullptr));
    } else {
        std::srand(seed);
    }
}

void Simulation::initialize()
{
    m_trucks.clear();
    m_stations.clear();
    m_currentMinute = 0;

    m_trucks.reserve(m_numOfTrucks);
    m_stations.reserve(m_numOfStations);

    for (int i = 0; i < m_numOfTrucks; i++) {
        Truck truck(i);
        truck.setState(TruckState::MINING);
        truck.setRemainingMinutes(generateMiningTimeInMinutes());
        truck.setStationId(-1);

        m_trucks.push_back(truck);
    }

    for (int i = 0; i < m_numOfStations; i++) {
        Station station(i);
        station.setCurrentTruckId(-1);
        station.setRemainingMinutesToUnload(0);

        m_stations.push_back(station);
    }
}

void Simulation::run()
{
    while (m_currentMinute < m_totalMinutes) {
        tick();
    }
}

void Simulation::printSummary() const
{
    int miningCount = 0;
    int travelingCount = 0;
    int waitingCount = 0;
    int unloadingCount = 0;
    int returningCount = 0;

    for (const Truck& truck : m_trucks) {
        switch (truck.state()) {
            case TruckState::MINING:
                ++miningCount;
                break;
            case TruckState::TRAVELING:
                ++travelingCount;
                break;
            case TruckState::WAITING:
                ++waitingCount;
                break;
            case TruckState::UNLOADING:
                ++unloadingCount;
                break;
            case TruckState::RETURNING:
                ++returningCount;
                break;
        }
    }

    std::cout << "\nSimulation Summary\n";
    std::cout << "------------------\n";
    std::cout << "Simulated minutes: " << m_currentMinute << "\n";
    std::cout << "Trucks: " << m_trucks.size() << "\n";
    std::cout << "Stations: " << m_stations.size() << "\n\n";

    std::cout << "Final truck states:\n";
    std::cout << "  MINING: " << miningCount << "\n";
    std::cout << "  TRAVELING: " << travelingCount << "\n";
    std::cout << "  WAITING: " << waitingCount << "\n";
    std::cout << "  UNLOADING: " << unloadingCount << "\n";
    std::cout << "  RETURNING: " << returningCount << "\n";

    std::cout << "Final station states:\n";
    for (const Station& station : m_stations) {
        std::cout << "  Station " << station.id() << ":\n";
        std::cout << "    Current truck ID: " << station.currentTruckId() << "\n";
        std::cout << "    Queue length: " << station.queueLength() << "\n";
        std::cout << "    Remaining unload time: " << station.remainingMinutesToUnload() << "\n";
    }
}

void Simulation::tick()
{
    updateStations();
    updateTrucks();
    processTruckArrivals();

    // advances simulated time
    ++m_currentMinute;
}

void Simulation::updateTrucks()
{
    for (Truck& truck : m_trucks) {
        TruckState state = truck.state();

        if (state == TruckState::WAITING || state == TruckState::UNLOADING) {
            continue;
        }

        // advances time for current task
        if (truck.remainingMinutes() > 0) {
            truck.setRemainingMinutes(truck.remainingMinutes() - 1);
        } 

        if (truck.remainingMinutes() > 0) {
            continue;
        }

        // Truck has completed current task
        if (state == TruckState::MINING) {
            truck.setState(TruckState::TRAVELING);
            truck.setRemainingMinutes(TRAVEL_TIME_IN_MINUTES);

        } else if (state == TruckState::RETURNING) {
            truck.setState(TruckState::MINING);
            truck.setRemainingMinutes(generateMiningTimeInMinutes());

        } else if (state == TruckState::TRAVELING) {
            // wait for processTruckArrivals() to assign a station.
        }
    }
}

void Simulation::updateStations()
{
    for (Station& station : m_stations) {
        // truck is currently unloading
        if (station.remainingMinutesToUnload() > 0) {
            // advance time by 1 minute
            
            // handle unload complete
            // set station to idle
        }

        // station is idle
        if (station.currentTruckId() == -1 && station.queueLength() > 0) {
            // start unloading next truck in queue
        }
    }
}

void Simulation::processTruckArrivals()
{
    for (Truck& truck : m_trucks) {
        // look for first available station

        // if all stations are busy, choose station with the shortest wait time

        // if station is idle, start unloading
    }
}

int Simulation::generateMiningTimeInMinutes()
{
    // currently using rand() for simplicity
    // prefer to use mt19937 + uniform_int_distribution for better randomness
    return std::rand() % (MAX_MINING_TIME_IN_MINUTES - MIN_MINING_TIME_IN_MINUTES + 1) + MIN_MINING_TIME_IN_MINUTES;
}