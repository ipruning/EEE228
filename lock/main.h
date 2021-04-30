#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"
#include "handle.h"

extern int row_1, row_2, row_3, row_4;

int user_input = 0;
char user_input_buffer[10] = {0};
int user_input_counter = 0;
long timer_input_begin = 0;
long timer_input_end = 0;

Ticker ticker_scan_column;
Ticker ticker_led;
Timer timer_input;

void ScanColumn(void);
char GetInput(void);
void FlashGreenLED(void);
void AppendBuffer(char input_array[10], int input, int *input_counter);
void DisplayInput(char input_array[10], int input_counter);