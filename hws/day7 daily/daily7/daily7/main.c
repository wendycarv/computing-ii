/*
Program: Parentheses!
Author: Wendy Carvalho
Date: 2/19/2023
Time spent: 5 hours
Purpose: The purpose of this program is to read strings of parentheses and say whether it is valid or not in regard to it being balanced or not.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Boolean test_case_is_valid(void);

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
    int n;
    int i;

    scanf("%d", &n);
    clear_keyboard_buffer();
    
    for (i = 0; i < n; i++)
    {
        if (test_case_is_valid())
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}

Boolean test_case_is_valid(void)
{
    char c;
    int noc;
    int counter = 0;
    Boolean answer;
    
    STACK hStack;
    hStack = stack_init_default();
    
    if (hStack == NULL)
    {
        printf("Failed to allocate space for stack object.\n");
        exit(1);
    }
    
    noc = scanf("%c", &c);
    
    while (noc == 1 && c != '\n')
    {
        if (c == '(' || c == '{' || c == '[')
        {
            stack_push(hStack, c);
            counter++;
        }
        
        else if ((c == ')' || c == '}' || c == ']') && stack_empty(hStack))
        {
            noc = scanf("%c", &c);
            while (c != '\n')
            {
                scanf("%c", &c);
            }
            return FALSE;
        }
       
        else if (c == ')' && (stack_top(hStack, NULL)) == '(')
        {
            stack_pop(hStack);
            counter++;
        }
        
        else if (c == ']' && (stack_top(hStack, NULL)) == '[')
        {
            stack_pop(hStack);
            counter++;
        }
        
        else if (c == '}' && (stack_top(hStack, NULL)) == '{')
        {
            stack_pop(hStack);
            counter++;
        }
        
        else if (c == ' ')
        {
            noc = scanf("%c", &c);
        }
        
        else
        {
            answer = FALSE;
            noc = scanf("%c", &c);
            while (noc == 1 && c != '\n')
            {
                scanf("%c", &c);
            }
        }
        
        if (c != '\n')
        {
            noc = scanf("%c", &c);
        }
    }
    
    if (counter % 2 == 0 && stack_empty(hStack))
    {
        answer = TRUE;
    }
    
    else
    {
        answer = FALSE;
    }

    if (!stack_empty(hStack))
    {
        stack_destroy(hStack);
    }
    
    return answer;
}

void clear_keyboard_buffer(void)
{
    char c;
    //int noc;
    //noc = scanf("%c", &c);
    scanf("%c", &c);
    while (c != '\n')
    {
        scanf("%c", &c);
    }
}
