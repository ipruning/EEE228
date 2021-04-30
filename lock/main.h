#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"

void ScanColumn(void);
void GetInput(int * input);

DigitalOut led(LED1);
Ticker timer;

void FlashLED(void)
{
    led = !led;
}