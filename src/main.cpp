#include <Arduino.h>

#include <iostream>

#include "WiFiManager.h"
#include "Ticker.h"
#include "OneButton.h"
#include "ACS712.h"

#include "NetworkClient.hpp"
#include "Event.hpp"
#include "FSMachine.hpp"

#include "config.hpp"

OneButton button(PUSH_BUTTON, true);
Ticker blinker;
Ticker memory;
ACS712 sensor(ACS712_05B, SENSOR);

NetworkClient networkClient = NetworkClient();
Event event = Event::IDLE;
FSMachine fsMachine = FSMachine();

const float blink_ok = 0.5;
const float blink_nok = 0.1;
const uint32_t pulse = 60000;

void blink(void)
{
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
}

void showStatus(void)
{
  std::cout << ">> " << millis() << "ms FreeHeap: " << ESP.getFreeHeap() << "b FreePsram: " << ESP.getFreePsram() << "b" << std::endl;
}

void reset(void)
{
  ESP.restart();
  delay(5000);
}

void setupWiFi(void)
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

  networkClient.begin();
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

  setupWiFi();

  blinker.attach(blink_ok, blink);
}

void loop()
{
  event = fsMachine.loop(event);

  if (networkClient.listen())
    event = Event::RECEIVED;

  if (event == Event::SEND)
  {
    networkClient.send();
    event = Event::SENT;
  }
}