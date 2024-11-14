#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

enum bridge_side { left, right };
typedef enum bridge_side BRIDGE_SIDE;


struct queue
{
    int cars;
    Node* front;
};

typedef struct queue Queue;


void test_case(Node** pHead)
{
    int i;
    int num_of_cars;
    int ferry_size;
    int car_length;
    char side[6];
                        
    QUEUE hLeft;
    hLeft = queue_init_default();
    
    QUEUE hRight;
    hRight = queue_init_default();
    
    scanf("%d %d", &ferry_size, &num_of_cars);

    ferry_size = ferry_size * 100; // meters to centimeters
    
    for (i = 0; i < num_of_cars; i++)
    {
        scanf(" %d %s", &car_length, side); // ADD CLEAR KEYBOARD BUFFER
                
        if (strcmp(side, "left") == 0)
        {
            queue_insert(hLeft, car_length); //the queue and its number in line
        }
        
        if (strcmp(side, "right") == 0)
        {
            queue_insert(hRight, car_length);
        }
    }
    
    tail_insert(pHead, cross_the_bridge(hLeft, hRight, ferry_size));
}

int cross_the_bridge(QUEUE hLeft, QUEUE hRight, int ferry_size)
{
    int ferry_trips = 0;
    int cars_serviced = 0;
    
    Queue* pLeft_queue = (Queue*)hLeft;
    Queue* pRight_queue = (Queue*)hRight;

    //ferry starts on left side
    BRIDGE_SIDE ferry_side = left;
    
    int ferry_space;
    ferry_space = ferry_size;
    
    while (!queue_is_empty(pLeft_queue) || !queue_is_empty(pRight_queue))
    {
        if (ferry_side == left)
        {
            cars_serviced = 0;
            
            while (!queue_is_empty(pLeft_queue)) //value = car_length
            {
                while (pLeft_queue->cars > 0  && ferry_space >= pLeft_queue->front->value)
                {
                    ferry_space -= pLeft_queue->front->value; //value = car_length
                    queue_service(hLeft);
                    cars_serviced++;
                }
            
                if (pLeft_queue-> cars == 0 || ferry_space < pLeft_queue->front->value)
                {
                    break;
                }
            }
            
            if (cars_serviced > 0 || (cars_serviced == 0 && !queue_is_empty(pRight_queue)))
            {
                ferry_side = right;
                ferry_trips++;
                ferry_space = ferry_size;
            }
        }
                    
        if (ferry_side == right)
        {
            cars_serviced = 0;
            
            while (!queue_is_empty(pRight_queue)) //value = car_length
            {
                while (pRight_queue->cars > 0  && ferry_space >= pRight_queue->front->value)
                {
                    ferry_space -= pRight_queue->front->value; //value = car_length
                    queue_service(hRight);
                    cars_serviced++;
                }
                if (pRight_queue-> cars == 0 || ferry_space < pRight_queue->front->value)
                {
                    break;
                }
            }
            
            if (cars_serviced > 0 || (cars_serviced == 0 && !queue_is_empty(pLeft_queue)))
            {
                ferry_side = left;
                ferry_trips++;
                ferry_space = ferry_size;
            }
        }
        
    }
    
    return ferry_trips;
}
               
QUEUE queue_init_default(void)
{
    Queue* pQ = (Queue*)malloc(sizeof(Queue));
    if (pQ != NULL)
    {
        pQ->cars = 0;
        pQ->front = (Node*)malloc(sizeof(Node));
        //pQ->tail = NULL;
        if (pQ->front == NULL)
        {
            free(pQ);
            return NULL;
        }
    }
    return pQ;
}

Status queue_insert(QUEUE hQ, int size) //side, car length and # in line ... inserting at tail
{
    Queue* pQ = (Queue*)hQ;
    
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        return FAILURE;
    }
    
    temp->value = size;
    temp->next = NULL;
    
    if (pQ->cars == 0) //empty case
    {
        pQ->front = temp;
    }
    else
    {
        Node* marker = pQ->front;
        while (marker->next != NULL)
        {
            marker = marker->next;
        }
        marker->next = temp;
    }
    
    pQ->cars++;
    return SUCCESS;
}

Status queue_service(QUEUE hQ) // deleting the head node from the linked list
{
    Queue* pQ = (Queue*)hQ;
    if(queue_is_empty(hQ)) // technically i already check for this inside cross_the_bridge
    {
        return FAILURE;
    }
   
    remove_head_node(&pQ->front);
    pQ->cars--;

    return SUCCESS;
}

Node* remove_head_node(Node** pHead)
{
    Node* temp;
    
    if (*pHead != NULL)
    {
        //move head pointer to next element of list
        temp = *pHead;
        *pHead = (*pHead)->next;
        free(temp); temp = NULL; // is this doing anything???
    }
   
    return *pHead;
}


Boolean queue_is_empty(QUEUE hQ)
{
    Queue* pQ = (Queue*)hQ;
    
    return (Boolean)(pQ->cars<= 0);
}

void queue_destroy(QUEUE* phQ)
{
    Queue* pQ = (Queue*)*phQ;
    Node* temp;
    
    while (pQ->front != NULL)
    {
        temp = pQ->front;
        pQ->front = pQ->front->next;
        free (temp);
    }
    
    free(pQ);
    *phQ = NULL;
}

void tail_insert(Node** pHead, int value)
{
    Node* answer;
    answer = (Node*)malloc(sizeof(Node));
    
    if (answer == NULL)
    {
        printf("failed to malloc\n");
        exit(1);
    }
    
    answer->value = value;
    answer->next = NULL;
    
    if (*pHead == NULL)
    {
        *pHead = answer;
    
    }
    else
    {
        Node* marker = *pHead;
        while (marker->next != NULL)
        {
            marker = marker->next;
        }
        marker->next = answer;
    }
}

void print_list(Node* head)
{
    while (head != NULL)
    {
        printf("%d\n", head->value);
        head = head->next;
    }
}

void destroy_node(Node* head)
{
    Node* temp;
    
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

