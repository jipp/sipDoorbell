#include <Arduino.h>
#include <unity.h>

#include <WiFi.h>

#include "config.hpp"

void setUp(void)
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP("esp32");
    WiFi.softAPsetHostname("esp32");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PUSH_BUTTON, INPUT_PULLUP);
}

void tearDown(void)
{
    // clean stuff up here
}

void hw_led(void)
{
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(LED_BUILTIN, LOW);
        TEST_ASSERT_EQUAL(digitalRead(LED_BUILTIN), LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        TEST_ASSERT_EQUAL(digitalRead(LED_BUILTIN), HIGH);
        delay(500);
    }
}

void hw_button()
{
    TEST_ASSERT_TRUE(digitalRead(PUSH_BUTTON));
}

void wifi(void)
{
    TEST_ASSERT_EQUAL(WiFi.getMode(), WIFI_AP);
    TEST_ASSERT_EQUAL_STRING(WiFi.softAPgetHostname(), "esp32");
}

void setup()
{
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!

    RUN_TEST(hw_led);
    RUN_TEST(hw_button);
    RUN_TEST(wifi);

    UNITY_END(); // stop unit testing
}

void loop()
{
}