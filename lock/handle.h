#ifndef HANDLE_H
#define HANDLE_H

#include <iostream>
#include <string>
#include "config.h"
#include "event.h"

char GetInput(void);
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);
void DisplayString(string input_string);

class PW
{
public:
    bool CheckPassword(void);
    bool CheckPasswordAdministrator(void);
    void UpdatePassword(void);
    void UpdatePasswordHash(char[]);
    bool UpdatePasswordFromUserInput(void);
    size_t GetHash(char[], int);
    void ResetUserInputBuffer(void);

    int user_input;                        // 用户输入
    int user_input_counter;                // 用户输入位数
    int user_check_counter;                // 用户误输次数
    char user_input_buffer[MAX_PW_LENGTH]; //
    int password_length;                   //
    size_t password_hash;                  //

    PW(char password_administrator_default[MAX_PW_LENGTH], char password_default[MAX_PW_LENGTH]); // PW() Constructor

private:
    char password[MAX_PW_LENGTH];               // Password
    char password_administrator[MAX_PW_LENGTH]; // Administrator Password
    int password_lifetime;                      // Password expiration
    char salt[11];                              // Salt for Hash
};

PW::PW(char password_administrator_default[MAX_PW_LENGTH], char password_default[MAX_PW_LENGTH])
{
    strcpy(password_administrator, password_administrator_default);
    strcpy(password, password_default);
    password_length = 5;
    user_check_counter = 0;
    // strcpy(salt, "jf7@qLy_u6Q*");
    // UpdatePasswordHash(password_default, password_length);
}

bool PW::CheckPassword(void)
{
    if (password_length != user_input_counter)
    {
        user_check_counter++;
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
                user_check_counter++;
                return false;
            }
        }
        user_check_counter = 0;
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

bool PW::CheckPasswordAdministrator(void)
{
    if (MAX_PW_LENGTH != user_input_counter) // Administrator password length is MAX_PW_LENGTH
    {
        user_check_counter++;
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
            if (temp[i] != password_administrator[i])
            {
                user_check_counter++;
                return false;
            }
        }
        user_check_counter = 0;
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

void PW::UpdatePassword(void)
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

bool PW::UpdatePasswordFromUserInput(void)
{
    DisplayString("GO");
    ResetUserInputBuffer();
    DisplayInput(user_input_buffer, user_input_counter);
    while (true)
    {
        user_input = GetInput();
        switch (user_input)
        {
        case '#':
            return true;
            break;
        case '*':
            ResetUserInputBuffer();
            DisplayInput(user_input_buffer, user_input_counter);
            break;
        default:
            if (user_input_counter >= MAX_PW_LENGTH)
            {
                user_input_counter = MAX_PW_LENGTH;
            }
            AppendBuffer(user_input_buffer, user_input, &user_input_counter);
            DisplayInput(user_input_buffer, user_input_counter);
            break;
        }
    }
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

void PW::ResetUserInputBuffer(void)
{
    user_input_counter = 0;
    for (int i = 0; i < MAX_PW_LENGTH; i++)
    {
        user_input_buffer[i] = '0';
    }
}

#endif