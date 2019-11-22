#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>

struct Socket
{
    std::string address;
    uint16_t port;
};

class Packet
{
public:
    Packet();
    ~Packet();
    Packet &operator=(const Packet &);

    Socket local;
    Socket remote;
    std::string payload;
};

#endif