#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <string>

struct Socket
{
    std::string address;
    uint16_t port;
};

class Packet
{
public:
    Packet(void);
    ~Packet();
    Packet &operator=(const Packet &);

    Socket local;
    Socket remote;
    std::string payload;
};

#endif