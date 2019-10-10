#ifndef NETWORK_CLIENT_HPP_
#define NETWORK_CLIENT_HPP_

#include <string>

#include <WiFi.h>
#include <WiFiUdp.h>

struct Socket
{
  std::string address;
  uint16_t port;
};

struct Packet
{
  Socket local;
  Socket remote;
  std::string payload;
};

class NetworkClient
{
public:
  NetworkClient(void);
  ~NetworkClient(void);

  bool begin(void);
  bool listen(void);
  bool send(void);

  Packet packet;

private:
  WiFiUDP udp;
};

#endif