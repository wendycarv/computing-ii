/*
    Program: Summing two linked lists
    Author: Wendy Carvalho
    Date: 02/13
    Time spent: 4 hours
    Purpose: The purpose of this program is to create two linked lists of digits, reverse them in order to add each # place together, and then create another linked list with the sum of those digits and print the result along with the original digits.
 */

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
    int data;
    Node* next;
};

void head_insert(Node** pHead, int value);

Node* reverse(Node* head);

void print_list(Node* head);

Node* list_sum(Node* head1, Node* head2);

void destroy_list(Node* head);

int main(int argc, char* argv[])
{
    // add up 189 + 11
    
    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* head_sum = NULL;
    
    //create a list for the number 189
    head_insert(&head1, 9);
    head_insert(&head1, 8);
    head_insert(&head1, 1);
    
    //create a list for the number 11
    head_insert(&head2, 1);
    head_insert(&head2, 1);

    head_sum = list_sum(head1, head2);
    
    printf("The sum of ");
    print_list(head1);
    printf(" + ");
    print_list(head2);
    printf("\n");
    printf(" = ");
    print_list(head_sum);
    printf("\n");
    
    //clean up three times
    destroy_list(head1); head1 = NULL;
    destroy_list(head2); head2 = NULL;
    destroy_list(head_sum); head_sum = NULL;
    
    return 0;
}

void head_insert(Node** pHead, int value)
{
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        printf("failed\n");
        exit(1);
    }
    
    temp->data = value;
    temp->next = *pHead;
    *pHead = temp;
}

Node* reverse(Node* head)
{
    Node* copy = NULL;
    Node* previous = NULL;
    Node* next = NULL;
    
    copy = head;
    
    if (copy == NULL || copy->next == NULL)
    {
        return copy;
    }
    
    while (copy != NULL)
    {
        previous = copy->next;
        copy->next = next;
        next = copy;
        copy = previous;
    }
    
    head = next;
    return head;
}

void print_list(Node* head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

Node* list_sum(Node* head1, Node* head2)
{
    Node* temp_head1;
    Node* temp_head2;

    Node* temp_sum;
    temp_sum = (Node*)malloc(sizeof(Node));
    
    if (temp_sum == NULL)
    {
        printf("Failed\n");
        exit(1);
    }
        
    Node* head_sum = NULL;

    head1 = reverse(head1);
    head2 = reverse(head2);
    
    temp_head1 = head1;
    temp_head2 = head2;
    
    int sum = 0;
    int extra = 0;
    int remainder;
        
    while (temp_head1 != NULL && temp_head2 != NULL)
    {
        sum = temp_head1->data + temp_head2->data + extra;
        remainder = sum % 10;
        
        if (sum >= 10)
        {
            temp_sum->data = remainder;
            extra = 1;
        }
        
        else if (sum < 10)
        {
            temp_sum->data = sum;
            extra = 0;
        }
        
        temp_head1 = temp_head1->next;
        temp_head2 = temp_head2->next;
        head_insert(&head_sum, temp_sum->data);
        temp_sum->next = (Node*)malloc(sizeof(Node));
        temp_sum = temp_sum->next;
    }

    if (temp_head1 == NULL)
    {
        while (temp_head2!=NULL)
        {
            temp_sum->data = temp_head2->data + extra;
            head_insert(&head_sum, temp_sum->data);
            temp_sum->next = (Node*)malloc(sizeof(Node));
            temp_sum = temp_sum->next;
            temp_head2 = temp_head2->next;
        }
    }
    
    else if (temp_head2 == NULL)
    {
        while (temp_head1!=NULL)
        {
            temp_sum->data = temp_head1->data + extra;
            head_insert(&head_sum, temp_sum->data);
            temp_sum->next = (Node*)malloc(sizeof(Node));
            temp_sum = temp_sum->next;
            temp_head1 = temp_head1->next;
        }
    }

    else if (temp_head1 == NULL && temp_head2 == NULL)
    {
        head_sum->data = 0;
        temp_sum->next = NULL;
    }

    head1 = reverse(head1);
    head2 = reverse(head2);

    return head_sum;
}

void destroy_list(Node* head)
{
    Node* temp;
    
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
