#include "main.h"
#include <iostream>
#include <string>

class PW
{
public:
    void UpdatePassword(char[], int);
    bool CheckPassword(void);
    unsigned long long GetHash(char[], int);

    int user_input;
    char user_input_buffer[MAX_PW_LENGTH] = {0};
    int user_input_counter;
    int password_length;
    unsigned long long password_hash;
    PW();

private:
    char salt[11];
    // char password[MAX_PW_LENGTH];
};

PW::PW(void)
{
    char password_default[MAX_PW_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '9'};
    // strcpy(password, password_default);
    password_length = 10;
    user_input = 0;
    user_input_counter = 0;

    strcpy(salt, "jf7@qLy_u6Q*");

    UpdatePassword(password_default, password_length);
}

void PW::UpdatePassword(char input[MAX_PW_LENGTH], int input_length)
{
    password_hash = GetHash(input, input_length);
}

bool PW::CheckPassword(void)
{
    char temp[MAX_PW_LENGTH] = {0};
    for (int i = 0; i < user_input_counter; i++)
    {
        temp[i] = user_input_buffer[user_input_counter - 1 - i];
    }
    
    if (password_length != user_input_counter)
    {
        return false;
    }
    else
    {
        if (GetHash(temp, user_input_counter) == password_hash)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// void PW::Reset()
// {
// }

unsigned long long PW::GetHash(char input[MAX_PW_LENGTH], int input_length)
{
    std::hash<std::string> hash;

    std::string str;
    for (int i = 0; i < input_length; i++)
    {
        str += std::to_string(input[i]);
    }

    return hash(strcat(&str[0], salt));
}

int main()
{
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    PW PW1;
    // ticker_led.attach(FlashGreenLED, 1000ms);
    while (true)
    {
        PW1.user_input = GetInput();
        ThisThread::sleep_for(INPUT_SENSITIVITY);
        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (PW1.user_input == '#')
            {
                // if (PW1.CheckPassword())
                // {
                //     ticker_led.attach(FlashGreenLED, 100ms);
                // }
                // else
                // {
                //     ticker_led.attach(FlashRedLED, 100ms);
                // }
                display.clear();
                display.Home();
                int tempint = PW1.password_hash % 10000;
                display.printf("%d", tempint);
                ThisThread::sleep_for(1000ms);
                PW1.user_input_counter = 0;
            }
            else if (PW1.user_input == '*')
            {
                ;
            }
            else
            {
                if (PW1.user_input != PW1.user_input_buffer[0])
                {
                    if (PW1.user_input_counter >= MAX_PW_LENGTH)
                    {
                        PW1.user_input_counter = 0;
                    }
                    AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    timer_input.reset();
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
                            PW1.user_input_counter = 0;
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
