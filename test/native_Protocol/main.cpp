#include "gtest/gtest.h"

#include "Protocol.hpp"

TEST(dummy, dummy)
{
}

TEST(Parse, undefined)
{
    Protocol protocol = Protocol();

    protocol.packet.local.address = "esp32";
    protocol.packet.local.port = 5060;
    protocol.packet.remote.address = "fritz.box";
    protocol.packet.remote.port = 5060;
    protocol.packet.payload = "";
    EXPECT_EQ((int)protocol.answer, 0);
    EXPECT_EQ(protocol.branch, "1234567890abcdef");
    EXPECT_EQ(protocol.local.tag, "34567890abcdef12");
    EXPECT_EQ(protocol.local.addr, "");
    EXPECT_EQ(protocol.remote.tag, "");
    EXPECT_EQ(protocol.remote.addr, "");
    EXPECT_EQ(protocol.callID, "234567890abcdef1");
    EXPECT_EQ(protocol.cSeq, 0);
    EXPECT_EQ(protocol.flow, "");
    EXPECT_EQ(protocol.realm, "");
    EXPECT_EQ(protocol.nonce, "");
}

TEST(Parse, 401)
{
    Protocol protocol = Protocol();

    protocol.packet.local.address = "esp32";
    protocol.packet.local.port = 5060;
    protocol.packet.remote.address = "fritz.box";
    protocol.packet.remote.port = 5060;
    protocol.packet.payload = "";
    protocol.packet.payload = std::string("SIP/2.0 401 Unauthorized\r\n") +
                              std::string("Via: SIP/2.0/UDP 192.168.178.20:5060;branch=JUw5bL3G89lQuHSX;rport=46718;alias\r\n") +
                              std::string("From: <sip:doorbell@192.168.178.1>;tag=8cPXEvfwbA15sP6K\r\n") +
                              std::string("To: <sip:doorbell@192.168.178.1>;tag=BFE65384385541CC\r\n") +
                              std::string("Call-ID: qfKvvLpcl6@192.168.178.20\r\n") +
                              std::string("CSeq: 1 REGISTER\r\n") +
                              std::string("WWW-Authenticate: Digest realm=\"fritz.box\", nonce=\"8FF3B1F255036289\"\r\n") +
                              std::string("User-Agent: FRITZ!OS\r\n") +
                              std::string("Content-Length: 0\r\n\r\n");
    protocol.parse();
    EXPECT_EQ((int)protocol.answer, 401);
    EXPECT_EQ(protocol.branch, "JUw5bL3G89lQuHSX");
    EXPECT_EQ(protocol.local.tag, "8cPXEvfwbA15sP6K");
    EXPECT_EQ(protocol.local.addr, "<sip:doorbell@192.168.178.1>");
    EXPECT_EQ(protocol.remote.tag, "BFE65384385541CC");
    EXPECT_EQ(protocol.remote.addr, "<sip:doorbell@192.168.178.1>");
    EXPECT_EQ(protocol.callID, "qfKvvLpcl6");
    EXPECT_EQ(protocol.cSeq, 1);
    EXPECT_EQ(protocol.flow, "REGISTER\r");
    EXPECT_EQ(protocol.realm, "fritz.box");
    EXPECT_EQ(protocol.nonce, "8FF3B1F255036289");
}

TEST(Parse, 500)
{
    Protocol protocol = Protocol();

    protocol.username = "username";
    protocol.packet.local.address = "esp32";
    protocol.packet.local.port = 5060;
    protocol.packet.remote.address = "fritz.box";
    protocol.packet.remote.port = 5060;
    protocol.packet.payload = "";
    protocol.packet.payload = std::string("SIP/2.0 500 Internal Server Error\r\n") +
                              std::string("Via: SIP/2.0/UDP 192.168.178.44:5060;branch=JUw5bL3G89lQuHSX;rport=5060;alias\r\n") +
                              std::string("From: <sip:doorbell@192.168.178.1>;tag=8cPXEvfwbA15sP6K\r\n") +
                              std::string("To: <sip:doorbell@192.168.178.1>;tag=B6EB7A8CBBD1811C\r\n") +
                              std::string("Call-ID: qfKvvLpcl6@192.168.178.44\r\n") +
                              std::string("CSeq: 1 REGISTER\r\n") +
                              std::string("User-Agent: FRITZ!OS\r\n") +
                              std::string("Content-Length: 0\r\n\r\n");
    protocol.parse();
    EXPECT_EQ((int)protocol.answer, 500);
    EXPECT_EQ(protocol.branch, "JUw5bL3G89lQuHSX");
    EXPECT_EQ(protocol.local.tag, "8cPXEvfwbA15sP6K");
    EXPECT_EQ(protocol.local.addr, "<sip:doorbell@192.168.178.1>");
    EXPECT_EQ(protocol.remote.tag, "B6EB7A8CBBD1811C");
    EXPECT_EQ(protocol.remote.addr, "<sip:doorbell@192.168.178.1>");
    EXPECT_EQ(protocol.callID, "qfKvvLpcl6");
    EXPECT_EQ(protocol.cSeq, 1);
    EXPECT_EQ(protocol.flow, "REGISTER\r");
    EXPECT_EQ(protocol.realm, "");
    EXPECT_EQ(protocol.nonce, "");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}