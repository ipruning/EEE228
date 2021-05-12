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
char output[] = "0000"; // 输出给屏幕的四位默认为 0

char input_buffer = '@';
long timer_input_begin = 0;
long timer_input_end = 0;

/*
function    
brief:      
param:      
return:     
*/
void ScanColumn(void);

/*
function    
brief:      
param:      
return:     
*/
char GetInput(void);

/*
function    
brief:      
param:      
return:     
*/
void ToggleGreenLED(void);

/*
function    
brief:      
param:      
return:     
*/
void ToggleRedLED(void);

/*
function    
brief:      
param:      
return:     
*/
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);

/*
function    
brief:      
param:      
return:     
*/
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);

/*
function    
brief:      
param:      
return:     
*/
void DisplayString(string input_string);

/*
function    
brief:      
param:      
return:     
*/
void FlashOperation(void);

#endif