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
    unsigned int* flags;

};
typedef struct bit_flags Bit_flags;


BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
    Bit_flags* pBit_flags = NULL;
    pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
    if (pBit_flags == NULL)
    {
        printf("Malloc failed returning NULL.\n");
        return NULL;
    }
    pBit_flags->size = number_of_bits;
    pBit_flags->capacity = 32 * 2;

    pBit_flags->flags = (unsigned int*)calloc(pBit_flags->capacity, sizeof(unsigned int));
    if (pBit_flags->flags == NULL)
    {
        printf("pBit_flags malloc failed.\n");
        return NULL;
    }
    return pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    int* temp;

    if (flag_position >= pBit_flags->capacity)
    {
        temp = (int*)calloc(pBit_flags->capacity * 2, sizeof(int));
        if (temp == NULL)
        {
            return FAILURE;
        }
        
        for (int i = 0; i < pBit_flags->capacity*2; i++)
        {
            temp[i] = pBit_flags->flags[i];


        }
        free(pBit_flags->flags);
        pBit_flags->flags = temp;
        pBit_flags->capacity *= 2;
    }

    pBit_flags->flags[flag_position] |= 1;
    


    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    int* temp;

    if (flag_position >= pBit_flags->capacity)
    {
        temp = (int*)calloc(pBit_flags->capacity * 2, sizeof(int));
        if (temp == NULL)
        {
            return FAILURE;
        }

        for (int i = 0; i < pBit_flags->capacity*2; i++)
        {
            temp[i] = pBit_flags->flags[i];
            //pBit_flags->size++;
        }
        free(pBit_flags->flags);
        pBit_flags->flags = temp;
        pBit_flags->capacity *= 2;
        pBit_flags->size = 118;

    }
    pBit_flags->flags[flag_position] &= ~1;
    

    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

    if (flag_position > pBit_flags->capacity)
    {
        return -1;
    }

    return pBit_flags->flags[flag_position];
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
    free(pBit_flags->flags);
    free(pBit_flags);

    *phBit_flags = NULL;

}
