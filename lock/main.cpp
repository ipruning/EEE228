#include "main.h"

int input = 0;

Ticker my_timer;
Ticker my_led;
SLCD display;

int main()
{
    int user_input = 0;
    my_timer.attach(ScanColumn, SCAN_COLUMN_PERIOD);
    my_led.attach(FlashGreenLED, 1000ms);

    while (true) {
        // ThisThread::sleep_for(1000ms);
        GetInput(&user_input);
        display.Home();
        display.printf("%d", user_input);
        printf("%d\n", user_input);
    }
}
