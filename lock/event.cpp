#include "event.h"

void ScanColumn(void)
{
    if (column_3 == 0)
    {
        column_1 = 0;
        column_2 = 1;
        column_3 = 1;
    } // only column_1 has the current
    else if (column_1 == 0)
    {
        column_1 = 1;
        column_2 = 0;
        column_3 = 1;
    } // same, but column_2
    else if (column_2 == 0)
    {
        column_1 = 1;
        column_2 = 1;
        column_3 = 0;
    } // column_3
    else
    {
        column_3 = 0;
    } // initialise this function
}

char GetInput(void)
{
    int input;
    digital_out_00.write(column_1); // write column_1 into d0 and output it to the keyboard
    digital_out_01.write(column_2);
    digital_out_02.write(column_3);
    row_1 = digital_in_00.read(); // read values inside the d3 returnning from the keyboard
    row_2 = digital_in_01.read();
    row_3 = digital_in_02.read();
    row_4 = digital_in_03.read();
    if (column_3 == 0 && row_4 == 0)
        input = '1';
    else if (column_2 == 0 && row_4 == 0)
        input = '2';
    else if (column_1 == 0 && row_4 == 0)
        input = '3';
    else if (column_3 == 0 && row_3 == 0)
        input = '4';
    else if (column_2 == 0 && row_3 == 0)
        input = '5';
    else if (column_1 == 0 && row_3 == 0)
        input = '6';
    else if (column_3 == 0 && row_2 == 0)
        input = '7';
    else if (column_2 == 0 && row_2 == 0)
        input = '8';
    else if (column_1 == 0 && row_2 == 0)
        input = '9';
    else if (column_3 == 0 && row_1 == 0)
        input = '*';
    else if (column_2 == 0 && row_1 == 0)
        input = '0';
    else
        input = '#';
    return input;
}

void FlashGreenLED(void)
{
    led_green = !led_green;
}

void AppendBuffer(char input_array[10], int input, int *input_counter)
{
    for (int i = 0; i < *input_counter; i++)
    {
        input_array[*input_counter - i] = input_array[*input_counter - 1 - i];
    }
    input_array[0] = input;
    *input_counter = *input_counter + 1;
}

void DisplayInput(char input_array[10], int input_counter)
{
    if (input_counter >= 4)
    {
        for (int i = 0; i < 4; i++)
        {
            output[3 - i] = input_array[i];
        }
    }
    else
    {
        for (int i = 0; i < input_counter; i++)
        {
            output[3 - i] = input_array[i];
        }
    }
    display.printf(output);
}
