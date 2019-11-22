#include "SimulateState.hpp"

SimulateState::SimulateState() = default;

SimulateState::~SimulateState() = default;

void SimulateState::entryAction(Event exitEvent, Protocol *protocol)
{
#ifdef UNIT_TEST
    if (exitEvent == Event::SEND)
        protocol->cSeqSimulate++;
#endif
}

void SimulateState::exitAction(Protocol *protocol)
{
}

bool SimulateState::guardAction(Event checkEvent, Protocol *protocol)
{
#ifdef UNIT_TEST
    if (checkEvent == Event::TRIGGER_SIMULATE_SINGLE_FAILED)
        return false;
#endif
    return true;
}

void SimulateState::timeAction(Protocol *protocol)
{
}