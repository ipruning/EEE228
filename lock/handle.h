#ifndef HANDLE_H
#define HANDLE_H

#include <iostream>
#include <string>
#include "config.h"
#include "event.h"

// Use the functions in Events.h
char GetInput(void);
void AppendBuffer(char input_array[MAX_PW_LENGTH], int input, int *input_counter);
void DisplayInput(char input_array[MAX_PW_LENGTH], int input_counter);
void DisplayString(string input_string);

// Thread
extern Thread thread_display;

// PW Class
class PW
{
public:
    bool CheckPassword(void);
    bool CheckPasswordAdministrator(void);
    void UpdatePassword(void);
    void UpdatePasswordAdministrator(void);
    void UpdatePasswordHash(char[]);
    bool UpdatePasswordFromUserInputToBuffer(void);
    size_t GetHash(char[], int);
    void ResetUserInputBuffer(void);

    char user_input;                       // The single character currently entered by the user
    char user_input_buffer[MAX_PW_LENGTH]; //
    int user_input_counter;                // Length of user-entered password
    int user_check_counter;                // Number of times a user has entered a password incorrectly

    int password_length;                // Length of password
    size_t password_hash;               // Hash of password
    size_t password_administrator_hash; // Hash of password

    PW(char password_administrator_default[MAX_PW_LENGTH], char password_default[MAX_PW_LENGTH]); // PW() Constructor

private:
    char password[MAX_PW_LENGTH];               // Password
    char password_administrator[MAX_PW_LENGTH]; // Administrator Password
    int password_lifetime;                      // Password expiration
    char salt[11];                              // Salt for Hash
};

/** PW Class Constructor
 * @param password_administrator_default Default password
 * @param password_default Default password
 */
PW::PW(char password_administrator_default[MAX_PW_LENGTH], char password_default[MAX_PW_LENGTH])
{
    strcpy(password_administrator, password_administrator_default);
    strcpy(password, password_default);
    password_length = 5;
    user_check_counter = 0;
    // strcpy(salt, "jf7@qLy_u6Q*");
    // UpdatePasswordHash(password_default, password_length);
}

// PW Class Methods

/** Check that the password is correct (compare to PW.password[]).
 * @return When True is returned, the password is correct.
 */
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

/** Check that the password is correct (compare to PW.password_administrator[]).
 * @return When True is returned, the password is correct.
 */
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

/** Save the passwords in the buffer to password array.
 */
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

/** Save the passwords in the buffer to password_administrator array.
 */
void PW::UpdatePasswordAdministrator(void)
{
    char temp[MAX_PW_LENGTH] = {0};
    for (int i = 0; i < user_input_counter; i++)
    {
        temp[i] = user_input_buffer[user_input_counter - 1 - i];
    }
    for (int i = 0; i < user_input_counter; i++)
    {
        password_administrator[i] = temp[i];
    }
    password_length = user_input_counter;
}

/** Save the hash of the password to the class.
 * @param input array
 */
void PW::UpdatePasswordHash(char input[MAX_PW_LENGTH])
{
    password_hash = GetHash(input, password_length);
}

/** Convert the input array to Hash with salt.
 * @param input Array
 * @param input_length Array length
 * @return hash
 */
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

/** Reset UserInputBuffer    
 */
void PW::ResetUserInputBuffer(void)
{
    user_input_counter = 0;
    for (int i = 0; i < MAX_PW_LENGTH; i++)
    {
        user_input_buffer[i] = '0';
    }
}

/** UpdatePasswordFromUserInputToBuffer -> Save the input to the buffer
 * @return Quit the function when the user enters #.
 */
bool PW::UpdatePasswordFromUserInputToBuffer(void)
{
    while (true)
    {
        if (GetInput() != '#')
            break;
    }
    thread_display.terminate();   // terminate current thread object
    thread_display.~Thread();     // destroy the local thread object
    new (&thread_display) Thread; // create new

    ResetUserInputBuffer();
    DisplayString("GO");
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

#endif