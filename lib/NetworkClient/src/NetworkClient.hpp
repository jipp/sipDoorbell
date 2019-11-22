#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP

#include <string>

#include "Packet.hpp"
#include "WiFi.h"
#include "WiFiUdp.h"

class NetworkClient
{
public:
  NetworkClient();
  NetworkClient(std::string const &, uint16_t);
  ~NetworkClient();

  bool begin(Packet *);
  bool listen(Packet *);
  bool send(Packet *);

private:
  WiFiUDP udp;
  std::string server;
  uint16_t port;
};

#endif