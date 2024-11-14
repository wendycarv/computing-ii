#ifndef queue_h
#define queue_h
#include "status.h"

typedef void* QUEUE;

struct node;

typedef struct node Node;

struct node
{
    int value;
    Node* next;
};

void test_case(Node** pHead);

int cross_the_bridge(QUEUE hLeft, QUEUE hRight, int ferry_size);

void destroy_node(Node* head);

void head_insert(Node** pHead, int value);

void tail_insert(Node** pHead, int value);

void print_list(Node* head);

Node* remove_head_node(Node** pHead);

QUEUE queue_init_default(void);

Status queue_insert(QUEUE hQ, int size);

Status queue_service(QUEUE hQ);

Boolean queue_is_empty(QUEUE hQ);

void queue_destroy(QUEUE* phQ);

#endif

