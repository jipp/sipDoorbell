#include "IdleState.hpp"

#include <iostream>

IdleState::IdleState()
{
    std::cout << "IdleState::IdleState" << std::endl;
}

IdleState::~IdleState()
{
}

void IdleState::entryAction(void)
{
    std::cout << "IdleState::entryAction" << std::endl;
}

void IdleState::exitAction(void)
{
    std::cout << "IdleState::exitAction" << std::endl;
}

bool IdleState::guardAction(void)
{
    std::cout << "IdleState::guardAction" << std::endl;
    return true;
}

void IdleState::timeAction(void)
{
}