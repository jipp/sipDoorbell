#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdlib>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#ifdef ESP32
#include "MD5Builder.h"
#endif
#include "Packet.hpp"
#include "StatusCode.hpp"

struct values
{
    std::string tag;
    std::string addr;
};

class Protocol
{
public:
    Protocol();
    ~Protocol();

    Packet packet;
    uint16_t cSeq;
#ifdef UNIT_TEST
    uint16_t cSeqSimulate;
#endif
    uint16_t cSeqRegister;
    uint16_t cSeqInvite;
    uint16_t cSeqAck;
    values remote;
    values local;
    std::string username;
    std::string password;
    std::string phonenumber;
    std::string branch; // unique across space and time for all requests sent by a user agent
    StatusCode answer;
    std::string callID; // unique
    std::string flow;
    std::string realm;
    std::string nonce;

    void parse();
    std::string calcHash(const std::string &);

private:
    std::vector<std::string> lines;

    void tokenizePayload();
    std::string getToken(std::string const &, int);
    std::string getValue(std::string const &, std::string const &, std::string const &);
    std::string getRandomString(int);
};

#endif