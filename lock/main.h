#include "mbed.h"
#include "config.h"
#include "drivers/SLCD/SLCD.h"

DigitalOut led(LED1);
Ticker timer;

void UpdateLED(void)
{
    led = !led;
}