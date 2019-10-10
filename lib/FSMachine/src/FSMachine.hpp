#ifndef FS_MACHINE_HPP_
#define FS_MACHINE_HPP_

#include <chrono>

#include "State.hpp"
#include "Event.hpp"
#include "IdleState.hpp"
#include "SimulateState.hpp"

struct FSMatrix
{
    State *currentState;
    Event checkEvent;
    State *nextState;
    Event exitEvent;
    std::chrono::milliseconds timer;
};

class FSMachine
{
public:
    FSMachine();
    ~FSMachine();

    Event loop(Event);

private:
    std::chrono::milliseconds timeoutTimerStart;
    std::chrono::milliseconds resendTimerStart;
    State *currentState;
    IdleState idle;
    SimulateState simulate;
    FSMatrix fsMatrix[3] = {
        {&idle, Event::GENERATE, &simulate, Event::SEND, (std::chrono::milliseconds)0},
        {&simulate, Event::SENT, &simulate, Event::RECEIVE, (std::chrono::milliseconds)0},
        {&simulate, Event::RECEIVED, &idle, Event::IDLE, (std::chrono::milliseconds)0},
    };
};

#endif
