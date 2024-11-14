#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"

struct my_vector //known type
{
    int size;
    int capacity;
    int* data;
};

typedef struct my_vector My_vector;

MY_VECTOR my_vector_init_default(void)
{
    My_vector* pVector = (My_vector*) malloc(sizeof(My_vector));
    
    if (pVector != NULL)
    {
        pVector->size = 0;
        pVector->capacity = 1;
        pVector->data = (int*)malloc(sizeof(int)*pVector->capacity);
        
        if(pVector->data == NULL)
        {
            free(pVector);
            return NULL;
        }
        //other stuff
    }
    
    return pVector;
}

Boolean my_vector_is_empty(MY_VECTOR hVector)
{
    My_vector* pVector = (My_vector*)hVector;
    
    return (Boolean)(pVector->size <= 0); // the weak condition would be == 0
}

Status my_vector_push_back(MY_VECTOR hVector, int value)
{
    My_vector* pVector = (My_vector*)hVector;
    int* temp;
    int i;
    
    if (pVector->size >= pVector->capacity) //if there is not enough room then make room
    {
        temp = (int*) malloc(sizeof(int) * pVector->capacity * 2);
        if (temp == NULL)
        {
            return FAILURE;
        }
        for (i = 0; i < pVector->size; i++)
        {
            temp[i] = pVector->data[i];
        }
        free(pVector->data);
        pVector->data = temp;
        pVector->capacity *= 2;
    }
    
    pVector->data[pVector->size] = value;
    pVector->size++;
    return SUCCESS;
}

int my_vector_get_size(MY_VECTOR hVector)
{
    My_vector* pVector = (My_vector*)hVector;
    return pVector->size;
}

int my_vector_get_capacity(MY_VECTOR hVector)
{
    My_vector* pVector = (My_vector*)hVector;
    return pVector->capacity;
}

Status my_vector_pop_back(MY_VECTOR hVector)
{
    My_vector* pVector = (My_vector*)hVector;
    
    if (my_vector_is_empty(hVector)) //might slow program down because it's calling a function unnecessarily
    {
        return FAILURE;
    }
    
    pVector->size--;
    
    return SUCCESS;
}

int* my_vector_at(MY_VECTOR hVector, int index)
{
    My_vector* pVector = (My_vector*)hVector;
    if (index < 0 || index > pVector->size) //access out of bounds
    {
        return NULL;
    }
    
    return &pVector->data[index];
}

void my_vector_destroy(MY_VECTOR* phVector)
{
    My_vector* pVector = (My_vector*)*phVector;
    
    free(pVector->data); // free up data because size and capacity are just parts of the structure while data is dynamically allocating shit
    free(pVector); // just freeing up what it refers to
    *phVector = NULL;
    
    printf("Destroyification complete!\n");
}
