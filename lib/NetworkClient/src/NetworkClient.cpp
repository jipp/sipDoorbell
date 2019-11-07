#include "NetworkClient.hpp"

NetworkClient::NetworkClient(void) : server("fritz.box")
{
    port = 5060;
}

NetworkClient::NetworkClient(std::string const &server)
{
    this->server = server;
    port = 5060;
}

NetworkClient::NetworkClient(std::string const &server, uint16_t port)
{
    this->server = server;
    this->port = port;
}

NetworkClient::~NetworkClient(void)
{
}

bool NetworkClient::begin(Packet *packet)
{
    if (udp.begin(port) != 1)
        return false;

    packet->local.address = std::string(WiFi.localIP().toString().c_str());
    packet->local.port = port;
    packet->remote.address = server;
    packet->remote.port = port;

    return true;
}

bool NetworkClient::listen(Packet *packet)
{
    int payloadSize = udp.parsePacket();

    if (payloadSize)
    {
        char *payload = (char *)malloc(payloadSize + 1);

        udp.read(payload, payloadSize);
        payload[payloadSize] = '\0';

        // if (packet->remote.address != std::string(udp.remoteIP().toString().c_str()))
        //     if (packet->remote.port != udp.remotePort())
        //         return false;

        packet->payload = payload;

        free(payload);

        return true;
    }

    return false;
}

bool NetworkClient::send(Packet *packet)
{
    if (udp.beginPacket(packet->remote.address.c_str(), packet->remote.port) != 1)
        return false;

    udp.print(packet->payload.c_str());

    if (udp.endPacket() != 1)
        return false;

    return true;
}