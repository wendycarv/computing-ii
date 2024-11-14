/*
 Author: Wendy Carvalho
 Date: 1/20/2023
 Effort: 15 minutes
 Purpose: The purpose of this assignment is to demonstrate how the left shift operator works when a variable x is shifted over by one bit to the left. Then it displays its new value and stops when x is equal to zero.
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int x;
    int counter = 0;
    
    for (x = 1; x != 0; counter++)
    {
        printf("%d: %u\n", counter, x);
        x = x << 1;
    }
    
    return 0;
}
