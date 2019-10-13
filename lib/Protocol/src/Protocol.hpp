#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <cstdint>

class Protocol
{
public:
    Protocol(void);
    ~Protocol();

    uint16_t cSeq;
};

#endif