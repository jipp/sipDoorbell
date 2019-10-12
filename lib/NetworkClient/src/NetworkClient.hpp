#ifndef NETWORK_CLIENT_HPP_
#define NETWORK_CLIENT_HPP_

#include <string>

#include <WiFi.h>
#include <WiFiUdp.h>
#include "Packet.hpp"

class NetworkClient
{
public:
  NetworkClient(void);
  explicit NetworkClient(std::string const &);
  NetworkClient(std::string const &, uint16_t);
  ~NetworkClient(void);

  bool begin(Packet *);
  bool listen(Packet *);
  bool send(Packet *);

private:
  WiFiUDP udp;
  std::string server;
  uint16_t port;
};

#endif