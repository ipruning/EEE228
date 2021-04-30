#include "main.h"
#include <iostream>
#import <string>

class PW
{
    public:
        double a;
        void MyTest();
}
void PW::MyTest(void)
{
    return 0;
}

int main()
{
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    // ticker_led.attach(FlashGreenLED, 1000ms);
    while (true)
    {
        user_input = GetInput();
        ThisThread::sleep_for(INPUT_SENSITIVITY);
        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (user_input != user_input_buffer[0])
            {
                if (user_input_counter >= MAX_PW_LENGTH)
                {
                    user_input_counter = 0;
                }
                AppendBuffer(user_input_buffer, user_input, &user_input_counter);
                DisplayInput(user_input_buffer, user_input_counter);
                timer_input.reset();
            }
            else
            {
                timer_input_end = timer_input.read_us();
                timer_input.reset();
                timer_input.start();
                if ((timer_input_end - timer_input_begin) > INPUT_INTERVAL)
                {
                    AppendBuffer(user_input_buffer, user_input, &user_input_counter);
                    DisplayInput(user_input_buffer, user_input_counter);
                }
                timer_input_begin = timer_input.read_us();
            }
        }
    }
}
