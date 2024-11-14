//implementation file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"

struct node;
typedef struct node Node;

struct node
{
    int value;
    Node* next;
};


struct stack // Known type
{
    Node* head;
};

typedef struct stack Stack;

STACK stack_init_default(void)
{
    Stack* pStack = (Stack*)malloc(sizeof(Stack));
    if (pStack != NULL)
    {
        pStack->head = NULL;
        
    }
    return pStack;
}

Status stack_push(STACK hStack, int value)
{
    //hi there we're casting to the known type
    Stack* pStack = (Stack*)hStack;
    Node* temp;
    
    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        return FAILURE;
    }
    
    temp->value = value;
    temp->next = pStack->head;
    pStack->head = temp;
    
    return SUCCESS;
}

Boolean stack_empty(STACK hStack)
{
    Stack* pStack = (Stack*)hStack;
    
    return pStack->head == NULL; //will return 0 or 1, and will cast to Boolean
}

    Status stack_pop(STACK hStack)
    {
        Stack* pStack = (Stack*)hStack;
        Node* temp;

        if (stack_empty(hStack))
        {
            return FAILURE;
        }
        
        temp = pStack->head;
        pStack->head = pStack->head->next;
        free(temp);
        
        return SUCCESS;
    }

int stack_top(STACK hStack, Status* pStatus)
{
    Stack* pStack = (Stack*)hStack;
    
    if (stack_empty(hStack))
    {
        if(pStatus != NULL)
        {
            *pStatus = FAILURE;
        }
        return -1337;
    }
    if(pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
    return pStack->head->value;
}

void stack_destroy(STACK* phStack)
{
    //since you're passing in the address through the parameter, you have to dereference it
    Stack* pStack = (Stack*)*phStack;
    Node* temp;
    
    //get rid of list
    while (pStack->head != NULL)
    {
        temp = pStack->head;
        pStack->head = pStack->head->next;
        free(temp);
    }
    
    //get rid of footprint
    free(pStack);
    *phStack = NULL;
    
    printf("Destroyification complete!\n");
}
