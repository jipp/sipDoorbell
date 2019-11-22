#include <Arduino.h>

#include <iostream>

#include "ACS712.h"
#include "Event.hpp"
#include "FSMachine.hpp"
#include "NetworkClient.hpp"
#include "OneButton.h"
#include "Packet.hpp"
#include "Ticker.h"
#include "WiFiManager.h"

#include "config.hpp"

OneButton button(PUSH_BUTTON, true);
Ticker blinker;
Ticker memory;
ACS712 sensor(ACS712_05B, SENSOR);

Packet packet;
NetworkClient networkClient = NetworkClient(server, port);
Event event = Event::IDLE;
Protocol protocol = Protocol();
FSMachine fsMachine = FSMachine(username, password);

const float blink_ok = 0.5;
const float blink_nok = 0.1;
const uint32_t pulse = 60000;

void blink()
{
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
}

void showStatus()
{
  std::cout << ">> " << millis() << "ms FreeHeap: " << ESP.getFreeHeap() << "b FreePsram: " << ESP.getFreePsram() << "b" << std::endl;
}

void triggerCall()
{
  event = Event::TRIGGER_REGISTER;
#ifdef VERBOSE
  std::cout << "call triggered: " << (int)event << std::endl;
#endif
}

void reset()
{
  ESP.restart();
  delay(5000);
}

void setupWiFi()
{
  WiFiManager wifiManager;

  WiFi.mode(WIFI_STA);

  if (!digitalRead(PUSH_BUTTON))
  {
    blinker.detach();
    digitalWrite(BUILTIN_LED, LOW);

    wifiManager.resetSettings();
    delay(5000);

    reset();
  }

  wifiManager.setTimeout(180);
  wifiManager.setConnectTimeout(10);

#ifdef VERBOSE
  wifiManager.setDebugOutput(true);
#else
  wifiManager.setDebugOutput(false);
#endif

  WiFi.setHostname(hostname);

  if (!wifiManager.autoConnect(hostname))
  {
    reset();
  }

  networkClient.begin(&packet);
}

void setup()
{
  Serial.begin(460800);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT_PULLUP);

  std::cout << std::endl
            << "verbose: ";

#ifdef VERBOSE
  std::cout
      << "enabled" << std::endl
      << std::endl;
#else
  std::cout
      << "disabled" << std::endl
      << std::endl;
#endif

  memory.attach_ms(pulse, showStatus);
  blinker.attach(blink_nok, blink);
  button.attachClick(triggerCall);

  setupWiFi();

  blinker.attach(blink_ok, blink);
}

void loop()
{
  button.tick();

  event = fsMachine.loop(event, &packet);

  if (event == Event::SEND)
  {
    std::cout << "send:" << std::endl
              << packet.payload << std::endl;
    networkClient.send(&packet);
  }

  if (networkClient.listen(&packet))
  {
    std::cout << "received:" << std::endl
              << packet.payload << std::endl;
    event = Event::RECEIVED;
  }
}