#include "NetworkClient.hpp"

NetworkClient::NetworkClient(void)
{
    this->packet.local.address = "127.0.0.1";
    this->packet.local.port = 5060;
}

NetworkClient::~NetworkClient(void)
{
}

bool NetworkClient::begin(void)
{
    if (udp.begin(this->packet.local.port) != 1)
        return false;

    this->packet.local.address = std::string(WiFi.localIP().toString().c_str());

    return true;
}

bool NetworkClient::listen(void)
{
    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        char *packet = (char *)malloc(packetSize + 1);
        
        udp.read(packet, packetSize);
        packet[packetSize] = '\0';

        this->packet.remote.address = std::string(udp.remoteIP().toString().c_str());
        this->packet.remote.port = udp.remotePort();
        this->packet.payload = packet;

        free(packet);

        return true;
    }

    return false;
}

bool NetworkClient::send(void)
{
    if (udp.beginPacket(this->packet.remote.address.c_str(), this->packet.remote.port) != 1)
        return false;

    udp.print(this->packet.payload.c_str());

    if (udp.endPacket() != 1)
        return false;

    return true;
}