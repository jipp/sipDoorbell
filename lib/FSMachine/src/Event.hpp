#ifndef EVENT_HPP
#define EVENT_HPP

enum class Event
{
    IDLE,
    SEND,
    RECEIVED,
#ifdef UNIT_TEST
    TRIGGER_SIMULATE_SINGLE,
    TRIGGER_SIMULATE_DOUBLE,
    TRIGGER_SIMULATE_SINGLE_TWICE_SEND,
    TRIGGER_SIMULATE_SINGLE_TWICE_RECEIVE,
    TRIGGER_SIMULATE_SINGLE_FAILED,
#else
    TRIGGER_REGISTER,
#endif
};

#endif