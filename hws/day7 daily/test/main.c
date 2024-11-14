#include <stdio.h>
#include <stdlib.h>

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;

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

Boolean test_case_is_valid(void);

void clear_keyboard_buffer(void);

typedef void* STACK;

STACK stack_init_default(void);

Status stack_push(STACK hStack, char brace);

Status stack_pop(STACK hStack);

char stack_top(STACK hStack, Status* pStatus);

Boolean stack_empty(STACK hStack);

void stack_destroy(STACK* phStack);


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
