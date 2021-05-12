#include <iostream>
#include <string>
#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"
#include "handle.h"

extern int row_1, row_2, row_3, row_4;
extern long timer_input_begin;
extern long timer_input_end;

extern Timer timer_input;
Ticker ticker_scan_column;
Ticker ticker_led;

void ScanColumn(void);
char GetInput(void);
void ToggleGreenLED(void);
void ToggleRedLED(void);
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);
void DisplayString(string input_string);
void FlashOperation(void);