/*
 Author: Wendy Carvalho
 Date: 03/22/2023
 Effort: Many, many, many days
 Purpose: The purpose of this assignment is to create a BIT_FLAGS data structure and in it make an array that will display 0s and 1s depending on what "flag" of the 32 bytes has been set.
 Interface proposal: In my opinion, a print_flags function would be useful in order to properly display the flags instead of having it done in main.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#define CAP (sizeof(int) * 8)

struct bit_flags
{
    int size;
    int capacity;
    int* data;
};

typedef struct bit_flags Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
    int i;
    int j;
    int index = 0;
    
    Bit_flags* pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
        
    if (pBit_flags != NULL)
    {
        j = pBit_flags->size;
        
        pBit_flags->size = number_of_bits;
        pBit_flags->capacity = CAP;
        pBit_flags->data = (int*)malloc(sizeof(int) * pBit_flags->capacity);
        
        if (pBit_flags->data == NULL)
        {
            free(pBit_flags);
            return NULL;
        }
        
        for (i = 0; i < number_of_bits; i++)
        {
            if (i % CAP == 0 && i != 0)
            {
                index++;
            }
        }
        
        for (i = 0; i <= index; i++)
        {
            pBit_flags->data[i] = 0;
        }
       
    }
    
    return (BIT_FLAGS)pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags =(Bit_flags*)hBit_flags;

    int i;
    int x = 1;
    int old_index = pBit_flags->size / CAP;
    int new_index;
    int index;
    
    if (flag_position >= pBit_flags->size)
    {
        pBit_flags->size = flag_position + 1;
        
        new_index = pBit_flags->size / CAP;
        
        for (i = old_index + 1; i < new_index; i++)
        {
            pBit_flags->data[i] = 0;
        }
    }
    
    index = flag_position / CAP;
    
    x =  x << flag_position % CAP;
    pBit_flags->data[index] = pBit_flags->data[index] | x;
    
    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags =(Bit_flags*)hBit_flags;

    int i;
    int x = 1;
    int old_index = pBit_flags->size / CAP;
    int new_index;
    int index;
    
    if (flag_position > pBit_flags->size)
    {
        pBit_flags->size = flag_position + 1;
        
        new_index = pBit_flags->size / CAP;
        
        for (i = old_index + 1; i < new_index; i++)
        {
            pBit_flags->data[i] = 0;
        }
    }
    
    index = flag_position / CAP;
    
    x =  ~(x << flag_position % CAP);
    pBit_flags->data[index] = pBit_flags->data[index] & x;
    
    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    int index = flag_position / CAP;
    int x = 1;
    x = x << flag_position % CAP;

    //return (pBit_flags->data[index] & (flag_position)) != 0;
        
    if ((pBit_flags->data[index] & x) != 0)
    {
        return 1;
    }
    
    return 0;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;
    
    free(pBit_flags->data);
    free(pBit_flags);
    *phBit_flags = NULL;
}
