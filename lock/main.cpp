#include "mbed.h"

#define BLINKING_RATE     500ms

int main()
{
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
