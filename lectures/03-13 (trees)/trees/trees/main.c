#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
    int data;
    //int count; //counts the amount of the same value there is
    Node* left;
    Node* right;
};

void tree_insert_reference(Node** pRoot, int value);
Node* tree_insert_return(Node* root, int value);

void tree_destroy(Node* root);
void tree_print(Node* root);


//binary search tree: everything in the left subtree is smaller than the root and everything in the right subtree is greater than the root. if the tree is good, then the # of nodes in each subtree are roughly the same. very logarithmic (logn)
int main(int argc, const char * argv[])
{
    
    Node* root = NULL;
    
    tree_insert_reference(&root, 15);
    root = tree_insert_return(root, 3);

    printf("%d\n", root->left->data);
    return 0;
}

void tree_insert_reference(Node** pRoot, int value)
{
    if (*pRoot == NULL)
    {
        *pRoot = (Node*)malloc(sizeof(Node));
        if (*pRoot == NULL)
        {
            printf("Failed to allocate space for node.\n");
            exit(1);
        }
        (*pRoot)->data = value;
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
    }
    else if (value < (*pRoot)->data)
    {
        tree_insert_reference(&((*pRoot)->left), value);
    }
    else if (value < (*pRoot)->data)
    {
        tree_insert_reference(&((*pRoot)->right), value);
    }
    /*
     else //for multi-sets, which lets you have duplicates of values
    {
        count++
    }
     */
}

void tree_destroy(Node* root) //post-order traversal (visit operation is a free)
{
    if (root != NULL)
    {
        tree_destroy(root->left);
        tree_destroy(root->right);
        free(root);
    }
}

void tree_print(Node* root) //inorder traversal (visital operation is a print)
{
    if (root != NULL)
    {
        tree_print(root->left);
        printf("%d\n", root->data);
        tree_print(root->right);
    }
    
}


//bubble sort: iterate through the list of elements, comparing adjacent elements, and if they're not in order, put them in order and do this through the entire list n-1 times. at the end, the list will be in order

//if you're trying to remove a root, you need a new root. this new root can be the greatest number in the left subtree or the smallest node in the right subtree. use the right subtree node, preferred.

Node* tree_insert_return(Node* root, int value)
{
    if (root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));
        
        if (root == NULL)
        {
            printf("Failed to allocate space for node.\n");
            exit(1);
        }
        root->data = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value < root->data)
    {
        root->left = tree_insert_return(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = tree_insert_return(root->right, value);
    }

    
    return root;
}
