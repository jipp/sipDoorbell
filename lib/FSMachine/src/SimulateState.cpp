#include "SimulateState.hpp"
#include <iostream>

SimulateState::SimulateState()
{
}

SimulateState::~SimulateState()
{
}

void SimulateState::entryAction(void)
{
    std::cout << "SimulateState::entryAction" << std::endl;
}

void SimulateState::exitAction(void)
{
    std::cout << "SimulateState::exitAction" << std::endl;
}

bool SimulateState::guardAction(void)
{
    std::cout << "SimulateState::guardAction" << std::endl;
    return true;
}

void SimulateState::timeAction(void)
{
}