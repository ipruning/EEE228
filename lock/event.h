#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "bsp.h"
#include "config.h"

// Keypad Pins
extern DigitalIn digital_in_00;
extern DigitalIn digital_in_01;
extern DigitalIn digital_in_02;
extern DigitalIn digital_in_03;
extern DigitalOut digital_out_00;
extern DigitalOut digital_out_01;
extern DigitalOut digital_out_02;

// LED Pins
extern DigitalOut led_green;
extern DigitalOut led_red;

// Timer
extern Timer timer_input;

// Ticker
extern Ticker ticker_scan_column;

// Keypad
int column_1, column_2, column_3; // For controlling the Keypad
int row_1, row_2, row_3, row_4;   // For controlling the Keypad

// GetInput()
char input_buffer = '@';    // Used in GetInput() to record the last user input
long timer_input_begin = 0; // Used in GetInput() to record the time
long timer_input_end = 0;   // Used in GetInput() to record the time

/** This function will be bound to the Ticker to drive the Keypad
 */
void ScanColumn(void);

/** Get the user's single input from the keyboard.
 * @return Characters entered by the user
 */
char GetInput(void);

/** ToggleGreenLED
 */
void ToggleGreenLED(void);

/** ToggleRedLED
 */
void ToggleRedLED(void);

/** Put the input into an array with all the array elements shifted backwards one place.
 * @param input_array Arrays to hold new data
 * @param input User input
 * @param input_counter Length of the password already entered by the user
 */
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);

/** Show the array to the display.
 * @param input_array Arrays to hold new data
 * @param input_counter Length of the password already entered by the user
 */
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);

/** Scroll the string on the display
 * @param input_string string displayed on the monitor
 */
void DisplayString(string input_string);

/** Make the buzzer rings
 *
 * It will be called when emergency.
 */
void Buzzer(void);

/** Make the LEDs of the exit button toggle
 *
 * It will be called when emergency.
 */
void ExitButtonLED_Toggle(void);

/** Receive the buffer from other door strike in the company and send them new buffer
 *
 * The buffers received and transmited should be arrays of all of the door strike states(0: no prob, 1:emergency, 2:update software).
 *
 * @param buffer An array that include the flag bit.
 * @return An array that include the flag bit and the state of this door stike.
 */
int *WiFiTransmit(int *buffer);

/** Make the door strike open
 *
 * It will send the high level signal to switch on the relay to open the door strike.
 */
void DoorstrikeOpen(void);

/** Make the door strike close
 *
 * It will send the low level signal to switch off the relay to close the door strike.
 */
void DoorstrikeClose(void);

/** Write the code into flash
 *
 * The address should be the place wanted to store buffer.
 * @param buffer The pointer to the code buffer array.
 * @param address The address of the code array in flash.
 */
void FlashWrite(int *buffer, int address);

/** Read the code from flash
 *
 * The adress should be the place wanted to store buffer.
 * @param address The adress of the code array in flash.
 * @return The pointer to the code buffer array.
 */
int *FlashRead(int address);

/** Flash test
 */
void FlashOperation(void);

#endif