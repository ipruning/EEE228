#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"
#include "handle.h"

extern int row_1, row_2, row_3, row_4;

int user_input = 0;
char user_input_buffer[MAX_PW_LENGTH] = {0};
int user_input_counter = 0;
long timer_input_begin = 0;
long timer_input_end = 0;

Timer timer_input;
Ticker ticker_scan_column;
Ticker ticker_led;

void ScanColumn(void);
char GetInput(void);
void FlashGreenLED(void);
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);
