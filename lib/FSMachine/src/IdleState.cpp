#include "IdleState.hpp"

IdleState::IdleState() = default;

IdleState::~IdleState() = default;

void IdleState::entryAction(Event exitEvent, Protocol *protocol)
{
    protocol->answer = StatusCode::not_defined;
    protocol->remote.tag.clear();
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