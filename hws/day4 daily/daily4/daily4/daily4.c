/*
    Author: Wendy Carvalho
    Date: 01/29/2023
    Effort: 2 hours
    Purpose: The purpose of this assignment is to set the nth bit to 1 by using the AND and OR bitwise operators and the shifting operator << to move 1 over. Then, the program also is able to unset the "flag position", which is simply making it so that wherever there is a bit with 1 in it it changes back to a 0. 
 */

#include <stdio.h>

void set_flag(unsigned int* flag_holder, int flag_position);
void unset_flag(unsigned int* flag_holder, int flag_position);
int check_flag(unsigned int flag_holder, int flag_position);
void display_32_flags(unsigned int flag_holder);

int main(int argc, char* argv[])
{
    unsigned int flag_holder = 0;
    
    set_flag(&flag_holder, 3);
    set_flag(&flag_holder, 16);
    set_flag(&flag_holder, 31);
    
    display_32_flags(flag_holder);
    
    unset_flag(&flag_holder, 31);
    unset_flag(&flag_holder, 3);
    set_flag(&flag_holder, 9);
    
    display_32_flags(flag_holder);
    return 0;
}

void set_flag(unsigned int* flag_holder, int flag_position)
{
    *flag_holder = *flag_holder | (1 << flag_position);
}

void unset_flag(unsigned int* flag_holder, int flag_position)
{
    *flag_holder = *flag_holder & ~(1 << flag_position);
}

void display_32_flags(unsigned int flag_holder)
{
    int i;
    for (i=31; i>=0; i--)
      {
          printf("%d", check_flag(flag_holder, i));
          if(i%4 == 0)
          {
              printf(" ");
          }
      }
      printf("\n");
}

int check_flag(unsigned int flag_holder, int flag_position)
{
    return (flag_holder & (1 << flag_position)) != 0;
}





