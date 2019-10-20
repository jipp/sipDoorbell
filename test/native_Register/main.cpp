#include "gtest/gtest.h"

#include <iostream>

#include "Protocol.hpp"
#include "RegisterState.hpp"

TEST(DISABLED_dummy, dummy)
{
}

TEST(Register, without_authentication)
{
    std::string buffer;
    Protocol protocol = Protocol();
    RegisterState register_without_authentication = RegisterState();

    protocol.packet.local.address = "esp32";
    protocol.packet.local.port = 5060;
    protocol.packet.remote.address = "fritz.box";
    protocol.packet.remote.port = 5060;
    protocol.packet.payload = "";

    buffer = std::string("REGISTER sip:fritz.box SIP/2.0\r\n") +
             std::string("Via: SIP/2.0/UDP esp32:5060;branch=1234567890abcdef;rport\r\n") +
             std::string("Max-Forwards: 70\r\n") +
             std::string("From: username <sip:username@fritz.box>;tag=34567890abcdef12\r\n") +
             std::string("To: username <sip:username@fritz.box>\r\n") +
             std::string("Call-ID: 234567890abcdef1@esp32\r\n") +
             std::string("CSeq: 1 REGISTER\r\n") +
             std::string("Contact: <sip:username@esp32>\r\n") +
             std::string("Content-Length: 0\r\n\r\n");

    register_without_authentication.entryAction(Event::SEND, &protocol);
    EXPECT_EQ(protocol.packet.payload, buffer);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}