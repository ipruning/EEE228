#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"

void ScanColumn(void);
void GetInput(int * input);
void FlashGreenLED(void);

Ticker timer;