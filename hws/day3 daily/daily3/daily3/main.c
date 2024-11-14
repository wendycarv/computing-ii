/*
    Author: Wendy Carvalho
    Date: 01/27/2023
    Effort: Three days
    Purpose: The purpose of this assignment is to set the nth bit to 1 by using the AND and OR bitwise operators and the shifting operator << to move the 1 over.
 */

#include <stdio.h>

void set_flag(int* pFlag_holder, int flag_position);
int check_flag(int flag_holder, int flag_position);

int main(int argc, char* argv[])
{
    int flag_holder = 0;
    int i;
    
    set_flag(&flag_holder, 3);
    set_flag(&flag_holder, 16);
    set_flag(&flag_holder, 31);
    
    for (i=31; i>=0; i--)
    {
        printf("%d", check_flag(flag_holder, i));
        if(i%4 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}

// |= sets the bit at flag_position to 1 and moves it 1 bit over to the left, storing it in *pFlag_holder
void set_flag(int* pFlag_holder, int flag_position)
{
    *pFlag_holder = *pFlag_holder | (1 << flag_position);
}

int check_flag(int flag_holder, int flag_position)
{
    // when flag_holder and the position of the flag moved one bit over are AND'd together and the result isn't 0, return 1
    return (flag_holder & (1 << flag_position)) != 0;
}





