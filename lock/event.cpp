#include "event.h"

void ScanColumn(void)
{
    if (column_3 == 0)
    {
        column_1 = 0;
        column_2 = 1;
        column_3 = 1;
    }
    else if (column_1 == 0)
    {
        column_1 = 1;
        column_2 = 0;
        column_3 = 1;
    }
    else if (column_2 == 0)
    {
        column_1 = 1;
        column_2 = 1;
        column_3 = 0;
    }
    else
    {
        column_3 = 0;
    }
}

char GetInput(void)
{
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    char input;
    do
    {
        digital_out_00.write(column_1);
        digital_out_01.write(column_2);
        digital_out_02.write(column_3);
        row_1 = digital_in_00.read();
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

        for (int i = 0; i < INPUT_SENSITIVITY;) // ThisThread::sleep_for(INPUT_SENSITIVITY);
        {
            i++;
        }

        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (input == '#')
            {
                input_buffer = input;
                ticker_scan_column.detach();
                return '#';
            }
            else if (input == '*')
            {
                input_buffer = input;
                ticker_scan_column.detach();
                return '*';
            }
            else
            {
                timer_input_end = timer_input.elapsed_time().count();
                timer_input.reset();
                timer_input.start();
                if ((timer_input_end - timer_input_begin) > INPUT_INTERVAL)
                {
                    return input;
                }
                timer_input_begin = timer_input.elapsed_time().count();
            }
        }
    } while (1);
}

void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter)
{
    for (int i = 0; i < *input_counter; i++)
    {
        input_array[*input_counter - i] = input_array[*input_counter - 1 - i];
    }
    input_array[0] = input;
    *input_counter = *input_counter + 1;
}

void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter)
{
    char output[] = "0000"; // The four bits output to the display defaults to 0
    led_green = 1;
    led_red = 1;
    if (input_counter >= 4)
    {
        for (int i = 0; i < 4; i++)
        {
            output[3 - i] = input_array[i];
        }
    }
    else if (input_counter > 0)
    {
        for (int i = 0; i < input_counter; i++)
        {
            output[3 - i] = input_array[i];
        }
    }
    else if (input_counter == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            output[i] = '0';
        }
    }
    else
    {
        ;
    }
    display.printf(output);
}

void DisplayString(string input_string)
{
    string display_string("  ");
    display_string.append(input_string).append("  ");
    int length = display_string.length();

    for (int i = 0; i < length - 3; i++)
    {
        display.printf("%c", display_string[i]);
        display.printf("%c", display_string[i + 1]);
        display.printf("%c", display_string[i + 2]);
        display.printf("%c", display_string[i + 3]);
        ThisThread::sleep_for(300ms);
    }
    display.clear();
    display.Home();
}

void ToggleGreenLED(void)
{
    led_green = !led_green;
}

void ToggleRedLED(void)
{
    led_red = !led_red;
}

void FlashOperation(void)
{
    // #define DEVICE_FLASH 1

    FlashIAP PW_Flash;
    PW_Flash.init();
    int address = PW_Flash.get_flash_size() - 4096;
    // int *data = (int *)address;
    PW_Flash.erase(address, 4096);
    int numbers[10] = {0, 1, 10, 100, 1000, 10000, 1000000, 10000000, 100000000, 1000000000};
    PW_Flash.program(numbers, address, 4096);
}

// Template

void Buzzer(void)
{
}

void ExitButtonLED_Toggle(void)
{
}

int *WiFiTransmit(int *buffer)
{
    return 0;
}

void DoorstrikeOpen(void)
{
}

void DoorstrikeClose(void)
{
}

void FlashWrite(int *buffer, int address)
{
}

int *FlashRead(int address)
{
    return 0;
}