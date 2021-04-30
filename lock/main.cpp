#include "main.h"

int main()
{
    int counter = 0;
    SLCD display;
    timer.attach(UpdateLED, BLINKING_RATE);

    while (true) {
        ThisThread::sleep_for(SLEEP_PERIOD);
        printf("loop %d\n", counter++);
        display.Home();
        display.printf("%d", counter);
    }
}
