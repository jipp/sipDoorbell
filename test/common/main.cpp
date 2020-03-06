#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void dummy(void)
{
    // TEST_IGNORE();
    TEST_IGNORE_MESSAGE("on purpose");
}

void process()
{
    UNITY_BEGIN(); // IMPORTANT LINE!

    RUN_TEST(dummy);

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