#include "main.h"

int main()
{
    // Initialising the test array
    char user_password_administrator_default[MAX_PW_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '9'};
    char user_password_default[MAX_PW_LENGTH] = {'5', '4', '3', '2', '1'};

    // Instantiating PW Class
    PW PW1(user_password_administrator_default, user_password_default);

    // During system initialization, if the password is not read from flash, prompt the user
    // DisplayString("PLEASE SET PW");                              // Prompt the user to enter
    // ticker_led.attach(ToggleGreenLED, 100ms);                    //
    // PW1.UpdatePasswordFromUserInputToBuffer();                   // User input -> buffer[]
    // PW1.UpdatePassword();                                        // buffer[] -> password[]
    // DisplayString("DONE");                                       //
    // ticker_led.detach();                                         //
    // PW1.ResetUserInputBuffer();                                  // Reset
    // DisplayInput(PW1.user_input_buffer, PW1.user_input_counter); //

    // Show launch screen
    // PW1.ResetUserInputBuffer();
    // DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
    // thread_display.start(Display_Go);
    // GetInput();
    // DisplayString("PLEASE INPUT PW");

    // Starting
    PW1.ResetUserInputBuffer();
    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);

    while (true)
    {
        PW1.user_input = GetInput();

        switch (PW1.user_input)
        {

        // When the user enters #, the program enters the password change logic assuming that the user has not entered it before.
        // If the user has entered, the program checks that the password is correct.
        case '#':
            if (PW1.user_input_counter == 0)
            {
                thread_display.start(DisplayADInput);      // Please Input Administrator Password
                PW1.UpdatePasswordFromUserInputToBuffer(); // Wait for the user to enter the administrator password -> PW1.user_input_buffer[]
                if (PW1.CheckPasswordAdministrator())      // Check that the password is correct (Compare PW1.user_input_buffer[] with PW1.password_administrator[])
                {
                    thread_display.start(DisplayNewInput);                       // Prompt the user to enter
                    ticker_led.attach(ToggleGreenLED, 100ms);                    // Start flashing the green light
                    PW1.UpdatePasswordFromUserInputToBuffer();                   // User input -> PW1.user_input_buffer[]
                    PW1.UpdatePassword();                                        // PW1.user_input_buffer[] -> PW1.password[]
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
                ThisThread::sleep_for(PW_FALSE_SLEEP_PERIOD);
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
