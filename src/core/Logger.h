#pragma once
#include <string>
#include "core/Mediator.h"
#include "Types.h"

extern Mediator gMediator;
// Helper function that formats a log message and sends it as an event
inline void Log(const std::string& message) {
    Event logEvent(Events::Log::NEW_MESSAGE);
    logEvent.SetParam<std::string>(Events::Log::MESSAGE, message);
    gMediator.SendEvent(logEvent);
}
