#include <iostream>
#include <string>
#include "mbed.h"
#include "drivers/SLCD/SLCD.h"
#include "config.h"
#include "bsp.h"
#include "event.h"
#include "handle.h"

// Ticker
extern Ticker ticker_led;

// Thread

extern Thread thread_display;

// Function
void ScanColumn(void);
char GetInput(void);
void ToggleGreenLED(void);
void ToggleRedLED(void);
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);
void DisplayString(string input_string);
void DoorstrikeOpen(void);

// Functions used by thread_display
void DisplayADInput(void)
{
    DisplayString("PLEASE INPUT ADMINISTRATOR PW");
}

void DisplayNewInput(void)
{
    DisplayString("PLEASE INPUT NEW PW");
}

void DisplayGo(void)
{
    DisplayString("Go");
}