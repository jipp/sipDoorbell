#include "SimulateState.hpp"

SimulateState::SimulateState()
{
}

SimulateState::~SimulateState()
{
}

void SimulateState::entryAction(Event event)
{
}

void SimulateState::exitAction(Event event)
{
}

bool SimulateState::guardAction(Event event)
{
    if (event == Event::TRIGGER_SIMULATE_SINGLE_FAILED)
        return false;
    return true;
}

void SimulateState::timeAction(Event event)
{
}