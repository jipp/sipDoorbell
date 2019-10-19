#include "gtest/gtest.h"

#include <iostream>

#include "Protocol.hpp"
#include "RegisterState.hpp"

TEST(DISABLED_dummy, dummy)
{
}

TEST(Register, without_authentication)
{
    Protocol protocol = Protocol();
    RegisterState register_without_authentication = RegisterState();

    protocol.packet.local.address = "esp32";
    protocol.packet.local.port = 5060;
    protocol.packet.remote.address = "fritz.box";
    protocol.packet.remote.port = 5060;
    protocol.packet.payload = "";
/*     protocol.packet.payload = std::string("SIP/2.0 401 Unauthorized\r\n") +
                              std::string("Via: SIP/2.0/UDP 192.168.178.20:5060;branch=JUw5bL3G89lQuHSX;rport=46718;alias\r\n") +
                              std::string("From: <sip:doorbell@192.168.178.1>;tag=8cPXEvfwbA15sP6K\r\n") +
                              std::string("To: <sip:doorbell@192.168.178.1>;tag=BFE65384385541CC\r\n") +
                              std::string("Call-ID: qfKvvLpcl6@192.168.178.20\r\n") +
                              std::string("CSeq: 1 REGISTER\r\n") +
                              std::string("WWW-Authenticate: Digest realm=\"fritz.box\", nonce=\"8FF3B1F255036289\"\r\n") +
                              std::string("User-Agent: FRITZ!OS\r\n") +
                              std::string("Content-Length: 0\r\n\r\n");
    protocol.parse(); */

    register_without_authentication.entryAction(Event::SEND, &protocol);
    std::cout << protocol.packet.payload << std::endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}