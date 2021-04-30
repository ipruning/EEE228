#include "event.h"

void ScanColumn(void)
{
    if (column_3 == 0)
    {
        column_1 = 0;
        column_2 = 1;
        column_3 = 1;
    } // only column_1 has the current
    else if (column_1 == 0)
    {
        column_1 = 1;
        column_2 = 0;
        column_3 = 1;
    } // same, but column_2
    else if (column_2 == 0)
    {
        column_1 = 1;
        column_2 = 1;
        column_3 = 0;
    } // column_3
    else
    {
        column_3 = 0;
    } // initialise this function
}

void GetInput(int * input)
{
    digital_out_00.write(column_1); // write column_1 into d0 and output it to the keyboard
    digital_out_01.write(column_2);
    digital_out_02.write(column_3);
    row_1 = digital_in_00.read(); // read values inside the d3 returnning from the keyboard
    row_2 = digital_in_01.read();
    row_3 = digital_in_02.read();
    row_4 = digital_in_03.read();
    if (column_3 == 0 && row_4 == 0)
        * input = 1; // 1
    else if (column_2 == 0 && row_4 == 0)
        * input = 2; // 2
    else if (column_1 == 0 && row_4 == 0)
        * input = 3; // 3
    else if (column_3 == 0 && row_3 == 0)
        * input = 4; // 4
    else if (column_2 == 0 && row_3 == 0)
        * input = 5; // 5
    else if (column_1 == 0 && row_3 == 0)
        * input = 6; // 6
    else if (column_3 == 0 && row_2 == 0)
        * input = 7; // 7
    else if (column_2 == 0 && row_2 == 0)
        * input = 8; // 8
    else if (column_1 == 0 && row_2 == 0)
        * input = 9; // 9
    else if (column_3 == 0 && row_1 == 0)
        printf("clear");
        // clear = true; //"*", clear inputs
    else if (column_2 == 0 && row_1 == 0)
        * input = 0; // 0
    else
        ; // #
}