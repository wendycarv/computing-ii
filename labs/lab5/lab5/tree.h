#ifndef TREE_H
#define TREE_H
#include "generic_vector.h"
#include "my_string.h"

typedef void* TREE;

struct node;
typedef struct node Node;

struct node{
    Node* parent;
    Node* left;
    Node* right;
    MY_STRING key;
    GENERIC_VECTOR data;
};

struct tree;
typedef struct tree Tree;

struct tree{
    Node* root;
};

TREE tree_init_default(void);
Status tree_push(TREE hTree, MY_STRING key, MY_STRING item);
GENERIC_VECTOR tree_get_largest_family(TREE hTree, int print_running_total);
GENERIC_VECTOR tree_find_max(Node* root, int print_running_total);
void tree_destroy(TREE* phTree);
void tree_destroy_node(Node* pNode);
#endif
