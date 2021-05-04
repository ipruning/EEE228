#include "main.h"
#include <iostream>
#include <string>

class PW
{
public:
    // int GetPassword(void);
    void UpdatePassword(char[], int);
    bool CheckPassword(void);
    unsigned long long GetHash(char[], int);

    char user_input_buffer[MAX_PW_LENGTH];
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

    strcpy(salt, "jf7@qLy_u6Q*");

    UpdatePassword(password_default, password_length);
}

// int PW::GetPassword(void)
// {
//     return password[0];
// }

void PW::UpdatePassword(char input[MAX_PW_LENGTH], int input_length)
{
    password_hash = GetHash(input, input_length);
}

bool PW::CheckPassword(void)
{
    if (password_length != user_input_counter)
    {
        return false;
    }
    else
    {
        if (GetHash(user_input_buffer, user_input_counter) == password_hash)
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
                timer_input_end = timer_input.elapsed_time().count();
                timer_input.reset();
                timer_input.start();
                if ((timer_input_end - timer_input_begin) > INPUT_INTERVAL)
                {
                    if (user_input_counter >= MAX_PW_LENGTH)
                    {
                        user_input_counter = 0;
                    }
                    AppendBuffer(user_input_buffer, user_input, &user_input_counter);
                    DisplayInput(user_input_buffer, user_input_counter);
                }
                timer_input_begin = timer_input.elapsed_time().count();
            }
        }
    }
}
