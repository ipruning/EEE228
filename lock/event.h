#ifndef EVENT_H
#define EVENT_H

#include <string>
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

extern Timer timer_input;

extern Ticker ticker_scan_column;

int column_1, column_2, column_3;
int row_1, row_2, row_3, row_4;
char output[] = "0000"; // The four bits output to the display defaults to 0

char input_buffer = '@';
long timer_input_begin = 0;
long timer_input_end = 0;

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void ScanColumn(void);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
char GetInput(void);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void ToggleGreenLED(void);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void ToggleRedLED(void);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void DisplayString(string input_string);

/** 
 * function    
 * brief:      
 * param:      
 * return:     
 */
void FlashOperation(void);

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
int *WiFi_transmit(int *buffer);

/** Make the door strike open
 *
 * It will send the high level signal to switch on the relay to open the door strike.
 */
void Doorstrike_Open(void);

/** Make the door strike close
 *
 * It will send the low level signal to switch off the relay to close the door strike.
 */
void Doorstrike_Close(void);

/** Write the code into flash
 *
 * The address should be the place wanted to store buffer.
 * @param buffer The pointer to the code buffer array.
 * @param address The address of the code array in flash.
 */
void Flash_Write(int *buffer, int address);

/** Read the code from flash
 *
 * The adress should be the place wanted to store buffer.
 * @param address The adress of the code array in flash.
 * @return The pointer to the code buffer array.
 */
int *Flash_Read(int address);

#endif