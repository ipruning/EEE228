#include "SLCD.h"
#include "Ticker.h"
#include "mbed.h"

#include "system.h"

// Global variables
#include "my_define.h"

// Object
Ticker my_timer;
Ticker my_warn;
SLCD my_display;

#include "driver.h"
// variables
int c1, c2, c3; // the 1st, 2nd, 3ir column on keyboard, from right to left
const char cong[21][2] = {" ", " ", " ", "c", "o", "n", "g", "r", "a", "t", "u",
                          "l", "a", "t", "i", "o", "n", "s", " ", " ", " "};
struct pws
{ // pw sets
    int a[4] = {1, 2, 3, 4};
    int b[4] = {2, 3, 4, 5};
    int c[4] = {3, 4, 5, 6};
    int d[4] = {4, 5, 6, 7};
} set_pws;
int i_pw[4] = {}; // input pw
int repeat_times = 0;

/*
function    column_switch
brief:      clear all segments and inputed data
param:      control c1 c2 c3 current
return:     void
*/
void column_switch(void)
{
    if (c3 == 0)
    {
        c1 = 0;
        c2 = 1;
        c3 = 1;
    } // only c1 has the current
    else if (c1 == 0)
    {
        c1 = 1;
        c2 = 0;
        c3 = 1;
    } // same, but c2
    else if (c2 == 0)
    {
        c1 = 1;
        c2 = 1;
        c3 = 0;
    } // c3
    else
    {
        c3 = 0;
    } // initialise this function
}

/*
function    clear_input_buffer
brief:      clear all segments and inputed data
param:      
return:     void
*/
void clear_input_buffer(int *p_number, int input_word[4])
{
    my_display.clear(); // All segments off
    my_display.Home();  // moves the cursor back to the beginning of the display
    *p_number = 0;
    led_green = 1;
    led_red = 1;
    for (int i = 0; i < 4; i++)
        input_word[i] = 10; // init input pw memory
}

/*
function    display_pass_information
brief:      display some information
param:      
return:     void
*/
void display_pass_information()
{
    DigitalOut led_greenreen(LED1);
    led_greenreen = 0;
    for (int y = 0; y < 2; y++)
    { // repeat 2 times
        for (int j = 0; j < 18; j++)
        { // rolling display_pass_information
            my_display.puts(cong[j]);
            my_display.puts(cong[j + 1]);
            my_display.puts(cong[j + 2]);
            my_display.puts(cong[j + 3]);
            ThisThread::sleep_for(500ms);
        }
    }
    led_greenreen = 1;
    //*Door Opens waits enough time for the user to open the door and then locks
    // afterwards
}

/*
function    flash_led
brief:      flash LED
param:      
return:     void
*/
void flash_led() { led_red = !led_red; }

/*
function    check_pw
brief:      password checker
param:      
return:     void
*/
void check_pw(bool match, int *p_number)
{
    if (repeat_times == 0)
    {
        for (int y = 0; y < 4; y++)
        {
            if (i_pw[y] !=
                set_pws
                    .a[y])
            { // checks against the first pw in the structure
                match = false;
                // flash_led();
                break;
            } // exits the for loop if a digit is wrong
            else
                match = true;
        }
    }
    else if (repeat_times == 1)
    {
        for (int y = 0; y < 4; y++)
        {
            if (i_pw[y] !=
                set_pws
                    .b[y])
            { // checks against the second pw in the structure
                match = false;
                // flash_led();
                break;
            }
            else
                match = true;
        }
    }
    else if (repeat_times == 2)
    {
        for (int y = 0; y < 4; y++)
        {
            if (i_pw[y] !=
                set_pws
                    .c[y])
            { // checks against the third pw in the structure
                match = false;
                // flash_led();
                break;
            }
            else
                match = true;
        }
    }
    else if (repeat_times == 3)
    {
        for (int y = 0; y < 4; y++)
        {
            if (i_pw[y] !=
                set_pws
                    .d[y])
            { // checks against the fourth pw in the structure
                match = false;
                // flash_led();
                break;
            }
            else
                match = true;
        }
    }
    else
    {
        my_warn.attach(flash_led, SECOND);
        for (int y = 0; y < 4; y++)
        {
            if (i_pw[y] !=
                set_pws
                    .d[y])
            { // checks against the fourth pw in the structure
                match = false;
                // flash_led();
                break;
            }
            else
                match = true;
        }
    }

    if (match)
    {
        repeat_times = 0;
        my_warn.detach();
        display_pass_information();
        clear_input_buffer(p_number, i_pw);
    }
    else
    {
        repeat_times++;
        flash_led();
        ThisThread::sleep_for(100ms);
        flash_led();
        clear_input_buffer(p_number, i_pw);
    }
}

int main()
{
    int i = 0;               // inputed value
    int r1, r2, r3, r4;      // the 1st 2nd 3rd 4th row on keyboard, from bottom to top
    int number = 0;          // inputed digit numbers
    int *p_number = &number; // pointer of number

    my_timer.attach(column_switch, SHORT_PERIOD); // runs every 5ms
    clear_input_buffer(p_number, i_pw);

    while (true) // loop
    {
        bool clear = false; // clear input
        bool match = false;

        digital_out_00.write(c1); // write c1 into d0 and output it to the keyboard
        digital_out_01.write(c2);
        digital_out_02.write(c3);
        r1 = digital_in_00.read(); // read values inside the d3 returnning from the keyboard
        r2 = digital_in_01.read();
        r3 = digital_in_02.read();
        r4 = digital_in_03.read();

        // recognize single signal input by the crossover point
        if (c3 == 0 && r4 == 0)
            i = 1; // 1
        else if (c2 == 0 && r4 == 0)
            i = 2; // 2
        else if (c1 == 0 && r4 == 0)
            i = 3; // 3
        else if (c3 == 0 && r3 == 0)
            i = 4; // 4
        else if (c2 == 0 && r3 == 0)
            i = 5; // 5
        else if (c1 == 0 && r3 == 0)
            i = 6; // 6
        else if (c3 == 0 && r2 == 0)
            i = 7; // 7
        else if (c2 == 0 && r2 == 0)
            i = 8; // 8
        else if (c1 == 0 && r2 == 0)
            i = 9; // 9
        else if (c3 == 0 && r1 == 0)
            clear = true; //"*", clear inputs
        else if (c2 == 0 && r1 == 0)
            i = 0; // 0
        else
            ;                               //#
        ThisThread::sleep_for(LONG_PERIOD); // delay function

        if (clear)                              // when clear==true
            clear_input_buffer(p_number, i_pw); // pass the address
        else if (r1 * r2 * r3 * r4 == 0 &&
                 number <
                     4) // display the number only if pressed sth and clear==false
        {
            my_display.printf("%d", i); // prints i
            i_pw[number] = i;
            number++;
        }

        if (number == 4)
        { // only runs when 4 numbers have been inputted
            check_pw(match, p_number);
        }
    }
}