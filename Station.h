#pragma once

#include <cstddef>
#include <queue>

class Station {
public:
    explicit Station(int id) : m_id(id) {}

    int id() const { return m_id; }

    void enqueueTruck(int truckId) { m_truckQueue.push(truckId); }
    int dequeueTruck() { // queueLength() > 0
        int truckId = m_truckQueue.front();
        m_truckQueue.pop();
        return truckId;
    }
    std::size_t queueLength() const {return m_truckQueue.size(); }

    int currentTruckId() const { return m_currentTruckId; }
    void setCurrentTruckId(int truckId) { m_currentTruckId = truckId; }

    int remainingMinutesToUnload() const { return m_remainingMinutesToUnload; }
    void setRemainingMinutesToUnload(int minutes) {m_remainingMinutesToUnload = minutes; }

private:
    int m_id;
    std::queue<int> m_truckQueue;
    int m_currentTruckId = -1; // -1 = station is idle
    int m_remainingMinutesToUnload = 0;
    int m_trucksProcessed = 0;
};