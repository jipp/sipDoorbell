#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <thread>

#include "Event.hpp"
#include "FSMachine.hpp"

TEST(DISABLED_dummy, dummy)
{
}

TEST(Handshake, single)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Handshake, single_failed)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE_FAILED;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE_FAILED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Handshake, double)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_DOUBLE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_DOUBLE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Send, two_packets)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE_TWICE_SEND;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE_TWICE_SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Receive, two_packets)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE_TWICE_RECEIVE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE_TWICE_RECEIVE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Handshake, single_resend)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    std::this_thread::sleep_for((std::chrono::milliseconds)400);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Handshake, single_timeout)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    std::this_thread::sleep_for((std::chrono::milliseconds)4000);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

TEST(Handshake, single_unordered)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    event = Event::SEND;
    EXPECT_EQ(event, Event::SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    event = Event::TRIGGER_SIMULATE_SINGLE;
    EXPECT_EQ(event, Event::TRIGGER_SIMULATE_SINGLE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);

    event = Event::RECEIVED;
    EXPECT_EQ(event, Event::RECEIVED);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}