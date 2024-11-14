#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

//ITEM (*init_copy)(ITEM); // MY_STRING my_string_init_copy(MY_STRING hString)

ITEM integer_init_copy(ITEM hInt);
void integer_destroy(ITEM* phInt); //a generic destroy -> void (*destroy)(ITEM*)

int main(int argc, const char * argv[])
{
    GENERIC_VECTOR hVector;
    int i;
    
    hVector = generic_vector_init_default(integer_init_copy, integer_destroy);
    
    if (hVector == NULL)
    {
        printf("poop\n");
        exit(1);
    }
    
    for (i = 0; i < 10; i++)
    {
        if(generic_vector_push_back(hVector, &i) == FAILURE)
        {
            printf("poop\n");
            exit(1);
        }
        printf("%d/%d\n", generic_vector_get_size(hVector), generic_vector_get_capacity(hVector));
    }
    
    for (i = 0; i < generic_vector_get_size(hVector); i++)
    {
        printf("%d\n", (int*)(*generic_vector_at(hVector, i)));
    }
    generic_vector_destroy(&hVector);
    
    return 0;
}

//make a copy and return the address of where the function made a copy
ITEM integer_init_copy(ITEM hInt)
{
    int* pInt;
    int* pArg = (int*)hInt;
    
    pInt = (int*)malloc(sizeof(int));
    
    if (pInt != NULL)
    {
        //now you're at where pInt is and you're creating a copy of it
        *pInt = *pArg;
    }
    
    return pInt;
}

void integer_destroy(ITEM* phInt)
{
    int* pInt = (int*)*phInt;
    free(pInt);
    *phInt = NULL;
}
