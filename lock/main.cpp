#include "main.h"

int main()
{
    // Initialising the test array
    char user_password_administrator_default[MAX_PW_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '9'};
    char user_password_default[MAX_PW_LENGTH] = {'5', '4', '3', '2', '1'};

    // Instantiating PW
    PW PW1(user_password_administrator_default, user_password_default);

    // Show launch screen
    DisplayString("PLEASE INPUT PW");
    PW1.ResetUserInputBuffer();
    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);

    while (true)
    {
        PW1.user_input = GetInput();
        switch (PW1.user_input)
        {
        // When the user enters #, the program enters the password change logic assuming that the user has not entered it before. If the user has entered, the program checks that the password is correct.
        case '#':
            if (PW1.user_input_counter == 0)
            {
                DisplayString("PLEASE INPUT AD PW");       // Administrator Password
                PW1.UpdatePasswordFromUserInputToBuffer(); // Wait for the user to enter the administrator password
                if (PW1.CheckPasswordAdministrator())      // Check that the password is correct
                {
                    DisplayString("PLEASE INPUT NEW PW");                        // Prompt the user to enter
                    ticker_led.attach(ToggleGreenLED, 100ms);                    // Start flashing the green light
                    PW1.UpdatePasswordFromUserInputToBuffer();                   // User input -> buffer[]
                    PW1.UpdatePassword();                                        // buffer[] -> password[]
                    DisplayString("DONE");                                       //
                    ticker_led.detach();                                         // LED stops flashing
                    PW1.ResetUserInputBuffer();                                  // Reset
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter); //
                }
                else
                {
                    ticker_led.attach(ToggleRedLED, 100ms);
                    DisplayString("FAILED");
                    ticker_led.detach();
                    PW1.ResetUserInputBuffer();
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                }
            }
            else if (PW1.user_check_counter <= MAX_PW_INPUT_TIMES)
            {
                if (PW1.CheckPassword() || PW1.CheckPasswordAdministrator())
                {
                    ticker_led.attach(ToggleGreenLED, 100ms);
                    DisplayString("PASS");
                    DoorstrikeOpen(); // Open the door
                    ticker_led.detach();
                    PW1.ResetUserInputBuffer();
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    // #TODO 需要添加开门的函数
                }
                else
                {
                    ticker_led.attach(ToggleRedLED, 100ms);
                    DisplayString("FAILED");
                    ticker_led.detach();
                    PW1.ResetUserInputBuffer();
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                }
            }
            else
            {
                ticker_led.attach(ToggleRedLED, 100ms);
                DisplayString("Please try again later");
                ThisThread::sleep_for(PW_FALSE_SELLP_PERIOD);
                ticker_led.detach();
                PW1.ResetUserInputBuffer();
                DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                PW1.user_check_counter = 0;
            }
            break;
        // Resets the input when the user enters *.
        case '*':
            PW1.ResetUserInputBuffer();
            DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
            break;
        // When the user enters 1-9 put the input into the buffer.
        default:
            if (PW1.user_input_counter >= MAX_PW_LENGTH)
            {
                PW1.user_input_counter = MAX_PW_LENGTH; // Preventing input overflow
            }
            AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
            DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
            break;
        }
    }
}
