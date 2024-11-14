#ifndef STACK_H
#define STACK_H

#include "status.h"

typedef void* STACK;

STACK stack_init_default(void);

//push
Status stack_push(STACK hStack, char brace);

//pop
Status stack_pop(STACK hStack);

//top
// Status stack_top(STACK hStack, int* pValue); //way 1
char stack_top(STACK hStack, Status* pStatus); //way 2

//empty
Boolean stack_empty(STACK hStack);


void stack_destroy(STACK* phStack);

#endif

