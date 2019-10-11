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
};

struct FSMatrixTimer
{
    State *currentState;
};

class FSMachine
{
public:
    FSMachine();
    ~FSMachine();

    Event loop(Event);

private:
    const std::chrono::milliseconds resendTimer = (std::chrono::milliseconds)300;
    const std::chrono::milliseconds timeoutTimer = (std::chrono::milliseconds)3000;
    std::chrono::milliseconds timeoutTimerStart;
    std::chrono::milliseconds resendTimerStart;
    State *currentState;
    IdleState idle;
#ifdef UNIT_TEST
    SimulateState simulate_single;
    SimulateState simulate_double_without_authentication;
    SimulateState simulate_double_with_authentication;
    SimulateState simulate_single_twice_send_one;
    SimulateState simulate_single_twice_send_two;
    SimulateState simulate_single_twice_receive_one;
    SimulateState simulate_single_twice_receive_two;
    FSMatrix fsMatrix[11] = {
        {&idle, Event::TRIGGER_SIMULATE_SINGLE, &simulate_single, Event::SEND},
        {&simulate_single, Event::RECEIVED, &idle, Event::IDLE},

        {&idle, Event::TRIGGER_SIMULATE_DOUBLE, &simulate_double_without_authentication, Event::SEND},
        {&simulate_double_without_authentication, Event::RECEIVED, &simulate_double_with_authentication, Event::SEND},
        {&simulate_double_with_authentication, Event::RECEIVED, &idle, Event::IDLE},

        {&idle, Event::TRIGGER_SIMULATE_SINGLE_TWICE_SEND, &simulate_single_twice_send_one, Event::SEND},
        {&simulate_single_twice_send_one, Event::SEND, &simulate_single_twice_send_two, Event::SEND},
        {&simulate_single_twice_send_two, Event::RECEIVED, &idle, Event::IDLE},

        {&idle, Event::TRIGGER_SIMULATE_SINGLE_TWICE_RECEIVE, &simulate_single_twice_receive_one, Event::SEND},
        {&simulate_single_twice_receive_one, Event::RECEIVED, &simulate_single_twice_receive_two, Event::IDLE},
        {&simulate_single_twice_receive_two, Event::RECEIVED, &idle, Event::IDLE},
    };
    FSMatrixTimer fsMatrixTimer[7] = {
        {&simulate_single},
        {&simulate_double_without_authentication},
        {&simulate_double_with_authentication},
        {&simulate_single_twice_send_one},
        {&simulate_single_twice_send_two},
        {&simulate_single_twice_receive_one},
        {&simulate_single_twice_receive_two},
    };
#else
    FSMatrix fsMatrix[0] = {};
    FSMatrixTimer fsMatrixTimer[0] = {};
#endif
};

#endif
