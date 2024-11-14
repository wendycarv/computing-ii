#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"

int main(int argc, char* argv[])
{
    MY_VECTOR hVector;
    int i;
    
    hVector = my_vector_init_default();
    if(hVector == NULL)
    {
        printf("Failed to allocate space for hVector object.\n");
        exit(1);
    }
    
    if (my_vector_is_empty(hVector))
    {
        printf("Hooray!\n");
    }
    for (i = 0; i < 10; i++)
    {
        if (my_vector_push_back(hVector, i) == FAILURE)
        {
            printf("Failed to push_back %d\n", i);
            exit(1);
        }
        printf("%d/%d\n", my_vector_get_size(hVector), my_vector_get_capacity(hVector)); 
    }
        
    for (i = 0; i < my_vector_get_size(hVector); i++)
    {
        printf("Values-> %d:\n", *my_vector_at(hVector, i)); //you cna look at that value by dereferencing it and also gives you access to change the integer at that spot
    }
    
    while(!my_vector_is_empty(hVector))
    {
        my_vector_pop_back(hVector);
        printf("%d/%d\n", my_vector_get_size(hVector), my_vector_get_capacity(hVector));
    }
    
    my_vector_destroy(&hVector);
    return 0;
}
