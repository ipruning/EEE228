#include "main.h"

int main()
{
    PW PW1;
    led_green = !led_green;
    led_red = !led_red;
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    PW1.ResetUserInput();
    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
    while (true)
    {
        PW1.user_input = GetInput();
        ThisThread::sleep_for(INPUT_SENSITIVITY);
        // PW1.user_input = GetInput(); #TODO
        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (PW1.user_input == '#')
            {
                if (PW1.user_input_counter == 0)
                {
                    DisplayString("PRESS INPUT OLD PW");
                    // DisplayString("PRESS # TO CHANGE PASSWORD");
                    // DisplayString("PRESS OTHER TO CHANGE PW");
                    PW1.GetUserInputBuffer();
                    if (PW1.CheckPasswordAdministrator())
                    {
                        DisplayString("PLEASE INPUT NEW PW");
                        ticker_led.attach(ToggleGreenLED, 100ms);
                        PW1.GetUserInputBuffer();
                        PW1.UpdatePassword();
                        DisplayString("DONE");
                        PW1.ResetUserInput();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                        ticker_led.detach();
                    }
                    else
                    {
                        ticker_led.attach(ToggleRedLED, 100ms);
                        DisplayString("WRONG");
                        PW1.ResetUserInput();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                        ticker_led.detach();
                    }
                }
                else if (PW1.user_check_counter <= MAX_PW_INPUT_TIMES)
                {
                    if (PW1.CheckPassword())
                    {
                        ticker_led.attach(ToggleGreenLED, 100ms);
                        DisplayString("PASS");
                        PW1.ResetUserInput();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                        ticker_led.detach();
                        // #TODO 需要添加开门的函数
                    }
                    else
                    {
                        ticker_led.attach(ToggleRedLED, 100ms);
                        DisplayString("FAILED");
                        PW1.ResetUserInput();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                        ticker_led.detach();
                    }
                }
                else
                {
                    ticker_led.attach(ToggleRedLED, 100ms);
                    DisplayString("Please try again later");
                    ThisThread::sleep_for(PW_FALSE_SELLP_PERIOD);
                    PW1.ResetUserInput();
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    PW1.user_check_counter = 0;
                    ticker_led.detach();
                }
                // display.clear();
                // display.Home();
                // // int tempint = PW1.password_hash % 10000;
                // // display.printf("%d", tempint);
                // // display.printf("%d", PW1.password_hash);
                // display.printf("%c", PW1.user_input_buffer[3]);
                // // display.printf("%d", PW1.user_input_counter);
                // ThisThread::sleep_for(1000ms);
                // PW1.user_input_counter = 0;
            }
            else if (PW1.user_input == '*')
            {
                PW1.ResetUserInput();
                DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
            }
            else
            {
                if (PW1.user_input != PW1.user_input_buffer[0])
                {
                    timer_input.reset();
                    if (PW1.user_input_counter >= MAX_PW_LENGTH)
                    {
                        PW1.user_input_counter = MAX_PW_LENGTH; // #TODO
                    }
                    AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                }
                else
                {
                    timer_input_end = timer_input.elapsed_time().count();
                    timer_input.reset();
                    timer_input.start();
                    if ((timer_input_end - timer_input_begin) > INPUT_INTERVAL)
                    {
                        if (PW1.user_input_counter >= MAX_PW_LENGTH)
                        {
                            PW1.user_input_counter = MAX_PW_LENGTH;
                        }
                        AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    }
                    timer_input_begin = timer_input.elapsed_time().count();
                }
            }
        }
    }
}
