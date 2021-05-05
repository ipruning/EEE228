#include "main.h"
#include <iostream>
#include <string>

class PW
{
public:
    bool CheckPassword(void);
    void UpdatePassword(char[]);
    void UpdatePasswordHash(char[]);
    void ResetUserInput(void);
    size_t GetHash(char[], int);

    int user_input;
    int user_input_counter;
    char user_input_buffer[MAX_PW_LENGTH];
    int password_length;
    size_t password_hash;
    PW();

private:
    char password[MAX_PW_LENGTH];
    char salt[11];
};

PW::PW(void)
{
    char password_default[MAX_PW_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '9'};
    strcpy(password, password_default);
    password_length = 10;
    // strcpy(salt, "jf7@qLy_u6Q*");
    // UpdatePasswordHash(password_default, password_length);
}

bool PW::CheckPassword(void)
{
    if (password_length != user_input_counter)
    {
        return false;
    }
    else
    {
        char temp[MAX_PW_LENGTH] = {0};
        for (int i = 0; i < user_input_counter; i++)
        {
            temp[i] = user_input_buffer[user_input_counter - 1 - i];
        }
        for (int i = 0; i < password_length; i++)
        {
            if (temp[i] != password[i])
            {
                return false;
            }
        }
        return true;
    }
    // else
    // {
    //     if (GetHash(temp, user_input_counter) == password_hash)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
}

void PW::UpdatePassword(char input[MAX_PW_LENGTH])
{
    char temp[MAX_PW_LENGTH] = {0};
    for (int i = 0; i < user_input_counter; i++)
    {
        temp[i] = user_input_buffer[user_input_counter - 1 - i];
    }
    for (int i = 0; i < user_input_counter; i++)
    {
        password[i] = temp[i];
    }
    password_length = user_input_counter;
}

void PW::UpdatePasswordHash(char input[MAX_PW_LENGTH])
{
    password_hash = GetHash(input, password_length);
}

size_t PW::GetHash(char input[MAX_PW_LENGTH], int input_length)
{
    std::string str;
    for (int i = 0; i < input_length; i++)
    {
        str += std::to_string(input[i]);
    }
    std::hash<std::string> hash;
    size_t hash1 = hash(str);
    return hash1;
}

void PW::ResetUserInput(void)
{
    user_input_counter = 0;
    for (int i = 0; i < MAX_PW_LENGTH; i++)
    {
        user_input_buffer[i] = '0';
    }
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
                if (PW1.CheckPassword())
                {
                    ticker_led.attach(FlashGreenLED, 100ms);
                }
                else
                {
                    ticker_led.attach(FlashRedLED, 100ms);
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
                    if (PW1.user_input_counter >= MAX_PW_LENGTH)
                    {
                        PW1.user_input_counter = 0; // #TODO
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
