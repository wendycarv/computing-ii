/*
    Author: Wendy Carvalho
    Date: 02/01/2023
    Effort: 4 hours
    Purpose: The purpose of this assignment is to create an array of a # of integers, each having 32 bits, with the ability to set a "flag" at a specific bit (setting that bit to 1) in that integer. Then, the program also is able to unset that "flag", which is simply making it so that wherever there is a bit with 1 in it it changes back to a 0.
 */

#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[])
{
    unsigned int flag_holder[5] = { 0 };
    
    set_flag(flag_holder, 3);
    set_flag(flag_holder, 16);
    set_flag(flag_holder, 31);
    set_flag(flag_holder, 87);

    display_flags(flag_holder, 5);
    printf("\n\n");
    
    unset_flag(flag_holder, 31);
    unset_flag(flag_holder, 3);
    set_flag(flag_holder, 99);
    set_flag(flag_holder, 100);

    display_flags(flag_holder, 5);
    return 0;
}

void set_flag(unsigned int flag_holder[], int flag_position)
{
    int x = 1;
    int index = flag_position / 32;
    
    x =  x << flag_position % 32;
    flag_holder[index] = flag_holder[index] | x;
}

void unset_flag(unsigned int flag_holder[], int flag_position)
{
    int x = 1;
    int index = flag_position / 32;
    
    x = ~(x << (flag_position % 32));
    flag_holder[index] = flag_holder[index] & x; //~ and | ?
}

void display_flags(unsigned int flag_holder[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        display_flags_as_array(flag_holder[i]);
    }
}

void display_flags_as_array(unsigned int flag_holder)
{
    int i;
    for (i = 0; i < 32; i++)
      {
          if(i % 4 == 0 && i > 0)
          {
              printf(" ");
          }
          printf("%d", check_flag(&flag_holder, i));

      }
      printf("\n");
}

int check_flag(unsigned int flag_holder[], int flag_position)
{
    int x = 1;
    int index = flag_position / 32;
    
    x = x << flag_position % 32;
    if ((flag_holder[index] & x) != 0)
    {
        return 1;
    }
    
    return 0;
}






