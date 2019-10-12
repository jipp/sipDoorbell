#include "IdleState.hpp"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

void IdleState::entryAction(Event event, Protocol *protocol)
{
}

void IdleState::exitAction(Event event, Protocol *protocol)
{
}

bool IdleState::guardAction(Event event, Protocol *protocol)
{
    return true;
}

void IdleState::timeAction(Event event, Protocol *protocol)
{
}