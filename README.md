# vast-take-home

# Lunar Helium-3 Mining Simulation

## Overview

This project implements a C++ simulation of a lunar Helium-3 mining operation over a 72-hour period.

The system models:
- mining trucks
- unload stations
- truck travel between mining sites and unload stations
- queueing behavior when all unload stations are busy

The simulation uses a **1-minute time-step model**.

## Design Approach

### High-level structure

- `Simulation`
  - Owns the simulation loop and overall orchestration
  - Advances simulated time minute by minute
  - Coordinates truck and station state transitions

- `Truck`
  - Stores truck-specific state
  - Tracks current state, remaining time, and assigned station

- `Station`
  - Stores unload-station-specific state
  - Owns the waiting queue, current unloading truck, and remaining unload time

### Simulation model

Truck states:
- `MINING`
- `TRAVELING`
- `WAITING`
- `UNLOADING`
- `RETURNING`

### Key Decisions

- Time-step simulation (1-minute granularity).
- Clear separation of responsibilities:
  - Simulation = orchestration and per-tick progression
  - Truck = truck lifecycle state
  - Station = unload queue state and unload timing
- Use of simple sentinel values (`-1`) to represent unassigned states

## Current Status

Implemented:
- Project structure and buildable executable
- Simulation loop (`initialize`, `run`, `tick`)
- Truck lifecycle (mining, traveling, returning)
- Mining duration generation

Partially implemented / outlined (pseudocode):
- Station unload progression
- Truck arrival handling and station assignment
- Queue-based load balancing across stations
- Due to the arrival handling not being fully implemented, trucks will remain in the TRAVELING state after completing travel in the current version.

## Future Work

Update Summary
- Track per-truck throughput (number of completed trips)
- Track per-station utilization (number of trucks processed)
- Use these metrics to evaluate system efficiency and load balancing

## Assumptions / Simplifications

- Simulation runs in minutes (72 hours total)
- Mining time: 60–300 minutes
- Travel time: 30 minutes
- Unload time: 5 minutes
- `rand()` used for simplicity (would replace with `std::mt19937`)

## Build and Run

```bash
clang++ -std=c++17 main.cpp Simulation.cpp -o vast_take_home
./vast_take_home
```
