#include "Packet.hpp"

Packet::Packet(void) = default;

Packet &Packet::operator=(const Packet &Packet)
{
    this->payload = Packet.payload;
    // this->local.address = Packet.local.address;
    // this->local.port = Packet.local.port;
    // this->remote.address = Packet.remote.address;
    // this->remote.port = Packet.remote.port;

    return *this;
}

Packet::~Packet() = default;