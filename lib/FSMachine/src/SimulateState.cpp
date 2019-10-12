#include "SimulateState.hpp"

SimulateState::SimulateState()
{
}

SimulateState::~SimulateState()
{
}

void SimulateState::entryAction(Event event, Protocol *protocol)
{
    protocol->cSeq++;
    std::cout << (int)event << " " << std::endl;
}

void SimulateState::exitAction(Event event, Protocol *protocol)
{
}

bool SimulateState::guardAction(Event event, Protocol *protocol)
{
#ifdef UNIT_TEST
    if (event == Event::TRIGGER_SIMULATE_SINGLE_FAILED)
        return false;
#endif
    return true;
}

void SimulateState::timeAction(Event event, Protocol *protocol)
{
}