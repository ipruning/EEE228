#include "bsp.h"

// init Pins
DigitalIn digital_in_00(D3);
DigitalIn digital_in_01(D4);
DigitalIn digital_in_02(D5);
DigitalIn digital_in_03(D6);
DigitalOut digital_out_00(D0);
DigitalOut digital_out_01(D1);
DigitalOut digital_out_02(D2);

// init LEDs
DigitalOut led_green(LED1);
DigitalOut led_red(LED2);

// init Dieplay
SLCD display;

// init Timer
Timer timer_input;

// init Ticker
Ticker ticker_scan_column;
Ticker ticker_led;

// init Thread

Thread thread_display;