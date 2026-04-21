#pragma once

enum class TruckState {
    MINING, // 60-300 minutes
    TRAVELING, // 30 minutes
    WAITING,
    UNLOADING,
    RETURNING // 30 minutes
};

class Truck {
public:
    explicit Truck(int id) : m_id(id) {}

    int id() const { return m_id; }

    TruckState state() const { return m_state;}
    void setState(TruckState state) { m_state = state; }

    int remainingMinutes() const { return m_remainingMinutes; }
    void setRemainingMinutes(int minutes) { m_remainingMinutes = minutes; }
    
    int stationId() const { return m_stationId; }
    void setStationId(int stationId) { m_stationId = stationId; }    

private:
    int m_id;
    TruckState m_state = TruckState::MINING;
    int m_remainingMinutes = 0;
    int m_stationId = -1; // -1 = unassigned
    int m_completedTrips = 0;
};