#include "game/Config.h"

#include "core/Mediator.h"
#include "core/Types.h"

extern Mediator gMediator;

Config& Config::GetInstance() {
    static Config instance;
    return instance;
}

