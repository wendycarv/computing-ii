#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include "status.h"

#include <stdio.h>

typedef void* MY_VECTOR;

MY_VECTOR my_vector_init_default(void);

//put things in the container (should add to end of the array so no shifting of other data that may already be in it needs to happen - NO LINEAR COST)
Status my_vector_push_back(MY_VECTOR hVector, int value);

//remove things, reorder?
Status my_vector_pop_back(MY_VECTOR hVector);

//resize
//look at and replace the value of elements in the container
int* my_vector_at(MY_VECTOR hVector, int index);

//does the vector contain an item?

//get the size
//get the capacity
int my_vector_get_size(MY_VECTOR hVector);
int my_vector_get_capacity(MY_VECTOR hVector);

//find out if the container is empty
Boolean my_vector_is_empty(MY_VECTOR hVector);

void my_vector_destroy(MY_VECTOR* phVector);

#endif
