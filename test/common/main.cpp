#include <unity.h>

void process()
{
    UNITY_BEGIN(); // IMPORTANT LINE!

    UNITY_END(); // stop unit testing
}

#ifdef ARDUINO

#include <Arduino.h>

void setup()
{
    delay(2000);

    process();
}

void loop()
{
}

#else

int main(int argc, char **argv)
{
    process();
    return 0;
}

#endif