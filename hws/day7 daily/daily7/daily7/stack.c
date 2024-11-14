#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node;
typedef struct node Node;

struct node
{
    char brace;
    Node* next;
};

struct stack
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

Status stack_push(STACK hStack, char brace)
{
    Stack* pStack = (Stack*)hStack;
    Node* temp;
    
    temp = (Node*)malloc(sizeof(Node));
    
    if (temp == NULL)
    {
        exit(1);
    }
    
    temp->brace = brace;
    temp->next = pStack->head;
    pStack->head = temp;
    
    return SUCCESS;
}

char stack_top(STACK hStack, Status* pStatus)
{
    Stack* pStack = (Stack*)hStack;
    
    if (stack_empty(hStack))
    {
        if(pStatus != NULL)
        {
            *pStatus = FAILURE;
        }
    }
    if(pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
    return pStack->head->brace;
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

Boolean stack_empty(STACK hStack)
{
    Stack* pStack = (Stack*)hStack;
    
    return pStack->head == NULL;
}

void stack_destroy(STACK* phStack)
{
    Stack* pStack = (Stack*)*phStack;
    pStack->head = NULL;
    free(pStack);
    *phStack = NULL;
}
