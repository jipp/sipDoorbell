#include "gtest/gtest.h"

#include <string>
#include <iostream>

#include "Event.hpp"
#include "FSMachine.hpp"

TEST(FSMachine, simple)
{
    Event event = Event::IDLE;
    FSMachine fsMachine = FSMachine();

    EXPECT_EQ(event, Event::IDLE);

    event = Event::GENERATE;
    EXPECT_EQ(event, Event::GENERATE);

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::SEND);

    event = Event::SENT;

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::RECEIVE);

    event = Event::RECEIVED;

    event = fsMachine.loop(event);
    EXPECT_EQ(event, Event::IDLE);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}