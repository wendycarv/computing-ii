#include <stdio.h>
#include <stdlib.h>

#include "generic_vector.h"
#include "generic.h"
#include "my_string.h"
#include "tree.h"

TREE tree_init_default(void)
{
    Tree* pTree = (Tree*)malloc(sizeof(Tree));
    if (pTree == NULL)
    {
        return NULL;
    }
    
    pTree->root = NULL;
    return pTree;
}

Status tree_push(TREE hTree, MY_STRING key, MY_STRING item) //HERE
{
    int num;
    Tree* pTree = (Tree*)hTree;

    if (pTree->root == NULL)
    {
        pTree->root = (Node*)malloc(sizeof(Node));
        if (pTree->root == NULL)
        {
            return FAILURE;
        }
        (pTree->root)->left = NULL;
        (pTree->root)->right = NULL;
        (pTree->root)->key = my_string_init_c_string(my_string_c_str(key));
        (pTree->root)->data = generic_vector_init_default(my_string_assignment_two, my_string_destroy);
    }
    else
    {
        //checking to see which has more letters
        num = my_string_compare((pTree->root)->key, key);
        //if the key at the root has more letters than the key we just got from the user's current guess
        if (num > 0)
        {
            //look at the node to the left (less than)
            tree_push(&((pTree->root)->right), key, item);
        }
            
        //if both keys have the same amount of letters revealed (user has guessed the word...yay)
        if (num == 0)
        {
            generic_vector_push_back((pTree->root)->data, item);
        }
        //if the user's current key has more letters revealed than the root on the tree
        if (num < 0)
        {
            //look at the node to the right (greater than)
            tree_push(&((pTree->root)->left), key, item);
        }
        else
        {
            return FAILURE;
        }
    }
    
    return SUCCESS;
}

GENERIC_VECTOR tree_get_largest_family(TREE hTree, int print_running_total)
{
    Tree* pTree = (Tree*)hTree;
    int i;
    GENERIC_VECTOR temp;
    GENERIC_VECTOR return_generic_vector = NULL;
    
    temp = tree_find_max(pTree->root, print_running_total);
    return_generic_vector = generic_vector_init_default(my_string_assignment_two, my_string_destroy);
    
    for (i = 0; i < generic_vector_get_size(temp); i++)
    {
        generic_vector_push_back(return_generic_vector, generic_vector_at(temp, i));
    }
    
    return return_generic_vector;
}


GENERIC_VECTOR tree_find_max(Node* root, int print_running_total)
{
    Generic_vector* temp = NULL;
    
    if (root != NULL)
    {
        if (root->left != NULL)
        {
            temp = tree_find_max(root->left, print_running_total);
            //compare how many words are associated with key
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data))
            {
                temp = root->data;
            }
        }
        
        if (root->right != NULL)
        {
            temp = tree_find_max(root->right, print_running_total);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data))
            {
                temp = root->data;
            }
        }
        
        if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data))
        {
            temp = root->data;
        }
    }
    
    //needs to print all the possibilities ig.....
    if (print_running_total == 1)
    {
        //print_the_tree(root);
        my_string_insertion(root->key, stdout);
        printf(" %d", generic_vector_get_size(root->data));
        printf("\n");
    }
    
    return temp;
}

/*
 void print_the_tree(Node* root)
{
    my_string_insertion(root->key, stdout);
    printf(" %d", generic_vector_get_size(root->data));
    printf("\n");
    
    if (root->left != NULL)
    {
        print_the_tree(root->left);
    }
    else if (root->right != NULL)
    {
        print_the_tree(root->right);
    }
}
 */

void tree_destroy(TREE* phTree)
{
    Tree* pTree = (Tree*)*phTree;
    
    if (pTree->root != NULL)
    {
        if ((pTree->root)->right != NULL)
        {
            tree_destroy_node((pTree->root)->left);
        }
        if ((pTree->root)->left != NULL)
        {
            tree_destroy_node((pTree->root)->right);
        }
        
        my_string_destroy(&((pTree->root)->key));
        generic_vector_destroy(&(pTree->root)->data);
        free(pTree->root);

    }
    
    free(pTree);
    *phTree = NULL;
}


void tree_destroy_node(Node* pNode)
{
    if (pNode == NULL)
    {
        return;
    }
    if (pNode->key != NULL)
    {
        my_string_destroy(&(pNode->key));
    }
    if (pNode->data != NULL)
    {
        generic_vector_destroy(&(pNode->data));
    }
     
    tree_destroy_node(pNode->left);
    tree_destroy_node(pNode->right);

    free(pNode);
}
