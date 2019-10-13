#include "SimulateState.hpp"

SimulateState::SimulateState()
{
}

SimulateState::~SimulateState()
{
}

void SimulateState::entryAction(Event exitEvent, Protocol *protocol)
{
    if (exitEvent == Event::SEND)
        protocol->cSeq++;
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