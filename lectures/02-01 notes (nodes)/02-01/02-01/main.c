#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
    int value;
    Node* next;
};

void print_list(Node* head);
void recursive_print_list(Node* head);

Node* returning_head_insert(Node* head, int value);
void reference_head_insert(Node** pHead, int value);

void reference_tail_insert(Node** pHead, int value);
void recursive_reference_tail_insert(Node** pHead, int value);
Node* recursive_returning_tail_insert(Node* head, int value);

void destroy_list(Node* head);

int main(int argc, const char * argv[])
{
    // 42 -> 43 -> 44 -> NULL
    Node* head = NULL;
    
    head = (Node*)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("no space dog.\n");
        exit(1);
    }
    head->value = 42;
    head->next = (Node*)malloc(sizeof(Node));
    
    if(head->next == NULL)
    {
        printf("no space dog.\n");
        exit(1);
    }
    
    head->next->value = 43;
    head->next->next = (Node*)malloc(sizeof(Node));
    
    if (head->next->next == NULL)
    {
        printf("no space dog.\n");
        exit(1);
    }
    
    head->next->next->value = 44;
    head->next->next->next = NULL;
    
    print_list(head);
    
    //reference_head_insert(&head, 44);
    //reference_head_insert(&head, 43);
    //reference_head_insert(&head, 42);

    //head = recursive_returning_tail_insert(head, 42);
    //head = recursive_returning_tail_insert(head, 43);
    //head = recursive_returning_tail_insert(head, 44);
    
    //head = returning_head_insert(head, 44);
    //head = returning_head_insert(head, 43);
    //head = returning_head_insert(head, 42);
    
    recursive_print_list(head);
    return 0;
    
}

void print_list(Node* head)
{
    while (head != NULL)
    {
        printf("%d\n", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

void recursive_print_list(Node* head)
{
    if (head != NULL)
    {
        printf("%d->", head->value);
        recursive_print_list(head->next);
    }
    else
    {
        printf("NULL\n");
    }
}

Node* returning_head_insert(Node* head, int value)
{
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    
    if (temp == NULL)
    {
        printf("Failed to alocate space for node.\n");
        exit (1);
    }
    temp->value = value;
    temp->next = head;
    return temp;
}

void reference_head_insert(Node** pHead, int value)
{
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    
    if (temp == NULL)
    {
        printf("Failed to alocate space for node.\n");
        exit (1);
    }
    temp->value = value;
    temp->next = *pHead;
    *pHead = temp;
}

void reference_tail_insert(Node** pHead, int value)
{
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));

    if (temp == NULL)
    {
        printf("Failed to alocate space for node.\n");
        exit (1);
    }
    
    temp->value = value;
    temp->next = NULL;
    
    if(*pHead == NULL) // empty case
    {
        *pHead = temp;
    }
    else
    {
        //list of one and list of many handled by same case.
        Node* marker = *pHead;
        while (marker->next != NULL)
        {
            marker = marker->next;
        }
        marker->next = temp;
    }
}

void recursive_reference_tail_insert(Node** pHead, int value)
{
    if (*pHead == NULL)
    {
        *pHead = (Node*)malloc(sizeof(Node));
        if (*pHead == NULL)
        {
            printf("Failed to allocate space for node.\n");
            exit(1);
        }
        (*pHead)->value = value;
        (*pHead)->next = NULL;
    }
    else
    {
        recursive_reference_tail_insert(&((*pHead)->next), value);
    }
}

Node* recursive_returning_tail_insert(Node* head, int value)
{
    if (head == NULL)
    {
        Node * temp;
        temp = (Node*)malloc(sizeof(Node));
        if (temp == NULL)
        {
            printf("Failed.\n");
            exit(1);
        }
        temp->value = value;
        temp->next = NULL;
        return temp;
    }
    else
    {
        head->next = recursive_returning_tail_insert(head->next, value);
    }
    return head;
}

void destroy_list(Node* head)
{
    Node* temp;
    while(head!=NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void recursive_destroy_list(Node* head)
{
    if(head!=NULL)
    {
        recursive_destroy_list(head->next);
        free(head);
    }
}
/*
 head = (Node*)malloc(sizeof(Node));
 
 if (head == NULL)
 {
     printf("Failed to allocate space for first node.\n");
     exit(1);
 }
 
 (*head).value = 42;
 (*head).next = (Node*)malloc(sizeof(Node));
 if(head->next == NULL)
 {
     printf("Failed to allocate space for second node.\n");
     exit(1);
 }
 
 head->next->value = 43;
 head->next->next = (Node*)malloc(sizeof(Node));
 if(head->next->next == NULL)
 {
     printf("Failed to allocate space for third node.\n");
     exit(1);
 }
 
 head->next->next->value = 44;
 head->next->next->next = NULL;

 */
