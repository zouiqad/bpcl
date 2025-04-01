#pragma once
#include "core/Types.h"
#include "core/Event.h"

class Config {
public:
    // Simulation parameters.
    bool   autoplay         = true;
    bool simulationStarted = false;
    bool simulationFinished = false;

    // ========== Init Params =========
    // -- Zombie Params --
    int    baseZombieCount = 3;
    int    runnerZombieCount = 2;
    int    explosiveZombieCount = 1;
    // -- Survivor Params --
    int    baseSurvivorCount = 6;
    int    doctorSurvivorCount = 2;
    int    militarySurvivorCount = 1;

    // ========== Runtime Params =========
    // -- Zombie Params --
    int  explosiveZombieRange = 1;
    int    runnerZombieSteps      = 2;
    // -- Survivor Params --
    int militarySurvivorRange = 2;

    float  turnDuration        = 3.0f;
    int infectionSpeed = 1;

    static Config& GetInstance();
private:
    Config() = default;
};
