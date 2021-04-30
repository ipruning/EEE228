#ifndef EVENT_H
#define EVENT_H

#include "bsp.h"
#include "config.h"

extern DigitalIn digital_in_00;
extern DigitalIn digital_in_01;
extern DigitalIn digital_in_02;
extern DigitalIn digital_in_03;
extern DigitalOut digital_out_00;
extern DigitalOut digital_out_01;
extern DigitalOut digital_out_02;
extern DigitalOut led_green;
extern DigitalOut led_red;

int column_1, column_2, column_3;
int row_1, row_2, row_3, row_4;

void ScanColumn(void);
void GetInput(int * input);
void FlashGreenLED(void);

#endif