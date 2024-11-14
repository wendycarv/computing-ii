#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Boolean test_case_is_valid(void);

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{    int i;
    
    STACK hStack;
    hStack = stack_init_default();
    
    if (hStack == NULL)
    {
        printf("Failed to allocate space for stack object.\n");
        exit(1);
    }
    
    for (i=0; i<10 ; i++)
    {
        if ((stack_push(hStack, i)) == FAILURE)
        {
            printf("Failed to insert node for value %d\n,", i);
            exit (1);
        }
    }
    
    while (!stack_empty(hStack))
    {
        printf("pop! %d\n", stack_top(hStack, NULL));
        stack_pop(hStack);
    }
    
    stack_destroy(&hStack); // second bookend

    return 0;
}

Boolean test_case_is_valid(void)
{
    char c;
    int noc;
    //STACK hStack;
    
    noc = scanf("%c", &c);
    while (noc == 1 && c != '\n')
    {
        noc = scanf("%c", &c);
    }
    return FALSE;
}

void clear_keyboard_buffer(void)
{
    char c;
    int noc;
    noc = scanf("%c", &c);
    while (noc == 1 && c != 'n')
    {
        noc = scanf("%c", &c);
    }
}

