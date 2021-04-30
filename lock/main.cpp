#include "main.h"

void ScanColumn(void);
char GetInput(void);
void FlashGreenLED(void);

int user_input = 0;
char user_input_buffer[10] = {0};
int user_input_counter = 0;
char output[] = "0000";

SLCD display;
Ticker ticker_scan_column;
Ticker ticker_led;
Timer timer_input;

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

int main()
{
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    ticker_led.attach(FlashGreenLED, 1000ms);
    long begin = 0;
    long end = 0;

    while (true)
    {
        user_input = GetInput();
        ThisThread::sleep_for(10ms);
        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (user_input != user_input_buffer[0])
            {
                if (user_input_counter >= 10)
                {
                    user_input_counter = 0;
                }
                AppendBuffer(user_input_buffer, user_input, &user_input_counter);
                DisplayInput(user_input_buffer, user_input_counter);
                timer_input.reset();
            }
            else
            {
                end = timer_input.read_us();
                timer_input.reset();
                timer_input.start();
                if ((end - begin) > 100000)
                {
                    AppendBuffer(user_input_buffer, user_input, &user_input_counter);
                    DisplayInput(user_input_buffer, user_input_counter);
                }
                begin = timer_input.read_us();
            }
        }
    }
}
