#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

#include "Packet.hpp"
#include "StatusCode.hpp"

#ifdef ESP32
#include "MD5Builder.h"
#endif

struct values
{
    std::string tag;
    std::string addr;
};

class Protocol
{
public:
    Protocol(void);
    ~Protocol();

    Packet packet;
    uint16_t cSeq;
    uint16_t cSeqRegister;
    uint16_t cSeqInvite;
    uint16_t cSeqAck;
    values remote = {"", ""};
    values local = {"", ""};
    std::string username = "username";
    std::string password = "password";
    std::string phonenumber = "**621";
    std::string branch; // unique across space and time for all requests sent by a user agent
    StatusCode answer;
    std::string callID; // unique
    std::string flow;
    std::string realm;
    std::string nonce;

    void parse(void);
    std::string calcHash(const std::string &);

private:
    std::vector<std::string> lines;

    void tokenizePayload(void);
    std::string getToken(std::string, int);
    std::string getValue(std::string, std::string, std::string);
    std::string getRandomString(int);
};

#endif