#ifndef BSP_H
#define BSP_H

#include "mbed.h"
#include "rtos.h"
#include "drivers/SLCD/SLCD.h"

extern DigitalIn digital_in_00;
extern DigitalIn digital_in_01;
extern DigitalIn digital_in_02;
extern DigitalIn digital_in_03;
extern DigitalOut digital_out_00;
extern DigitalOut digital_out_01;
extern DigitalOut digital_out_02;

extern DigitalOut led_green;
extern DigitalOut led_red;

extern SLCD display;

extern Timer timer_input;

extern Ticker ticker_scan_column;
extern Ticker ticker_led;

extern Thread thread_display;

#endif