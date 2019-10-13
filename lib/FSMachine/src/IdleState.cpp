#include "IdleState.hpp"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

void IdleState::entryAction(Event exitEvent, Protocol *protocol)
{
}

void IdleState::exitAction(Protocol *protocol)
{
}

bool IdleState::guardAction(Event checkEvent, Protocol *protocol)
{
    return true;
}

void IdleState::timeAction(Protocol *protocol)
{
}