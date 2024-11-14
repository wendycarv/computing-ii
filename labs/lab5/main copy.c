#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "my_string.h"
#include "generic_vector.h"

ITEM integer_init_copy(ITEM hInt);
void integer_destroy(ITEM* phInt);
void prompt_user(void);

GENERIC_VECTOR* init_dictionary(void);

int main(int argc, char* argv[])
{
    GENERIC_VECTOR *dictionary = init_dictionary();
        
    MY_STRING test_word = my_string_init_c_string("The");
    MY_STRING key = my_string_init_default();
    MY_STRING current = my_string_init_default();
  
    int i;
    
    int test_word_size;
    test_word_size = my_string_get_size(test_word);
    //get_word_key_value(word_key, word_family, generic_vector_at(dictionary[word_length], i ), current_guess);

    for (i = 0; i < test_word_size; i++)
    {
        my_string_push_back(current, '-');
    }

    get_word_key_value(current, key, test_word, 'T');
    my_string_insertion(key, stdout);
    printf("\n");
    
    return 0;
}


GENERIC_VECTOR* init_dictionary(void)
{
    GENERIC_VECTOR *hVector = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * 30);
    MY_STRING hString = NULL;
    FILE* fp;
    int i;
    int string_size;
    
    char dictionary[] = "/Users/wendy/Documents/school/uml/spring 2023/comp ii lab/lab5/lab5/dictionary.txt";
    
    //fp = fopen("dictionary.txt", "r");
    fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        printf("Unable to open dictionary.txt\n");
        exit(1);
    }
    
    hString = my_string_init_default();
    if (hString == NULL)
    {
        printf("Failed to initialize string\n");
        exit(1);
    }
    
    //for 30
    for (i = 0; i < 30; i++)
    {
        hVector[i] = generic_vector_init_default(my_string_assignment_two,
        my_string_destroy);
        if (hVector[i] == NULL)
        {
            exit(1);
        }
    }
    
    while (my_string_extraction(hString, fp)) 
    {
        string_size = my_string_get_size(hString);
        
        //printf("String found: ");
        //my_string_insertion(hString, stdout);
        //printf("\n");
        
        if (string_size < 30)
        {
            if(!generic_vector_push_back(hVector[string_size], (ITEM)hString))
            {
                printf("Failed to push string of size %d from dictionary onto vector\n", string_size);
                exit(1);
            }
            //printf("Vector at words of size %d: ", string_size);
            //my_string_insertion(generic_vector_at(hVector[string_size], 0), stdout);
            //printf("\n");
        }
    }

    /*printf("Strings of size 3: \n");
    for (i = 0; i < my_string_get_size(hVector[3]); i++)
    {
        my_string_insertion(generic_vector_at(hVector[3], i), stdout);
        printf("\n");
    }
    */
    
    for (i = 0; i < 30; i++)
    {
        printf("Amount of words in Vector[%d]: %d\n", i, my_string_get_size(hVector[i]));
    }
               
    my_string_destroy(&hString);
    fclose(fp);
    
    return hVector;
}
ITEM integer_init_copy(ITEM hInt)
{
    int* pInt;
    int* pArg = (int*)hInt;
    pInt = (int*)malloc(sizeof(int));
    if (pInt != NULL)
    {
        *pInt = *pArg;
    }
    return pInt;
}

void integer_destroy(ITEM* phInt)
{
    int* pInt = (int*)*phInt;
    free(pInt);
    *phInt = NULL;
}

/*
int main(int argc, const char * argv[])
{
    int i;
    int a = 0;
    int b = 99;
        
    MY_STRING array[100] = { NULL };
    array[0] = my_string_init_c_string("COPY ME!");
    
    for (i = 1; i < 100; i++)
    {
        array[i] = my_string_init_copy(array[0]);
    }

    my_string_destroy(&array[0]);
    array[0] = my_string_init_c_string("FIRST FIFTY!");
    
    for (i = 1; i < 50; i++)
    {
        my_string_assignment(array[i], array[0]);
    }

    while (a != 50)
    {
        my_string_swap(array[a], array[b]);
        a++;
        b--;
    }
    
    for (i = 0; i < 100; i++)
    {
        my_string_insertion(array[i], stdout);
        printf("\n");
        my_string_destroy(&array[i]);
    }
     
    return 0;
}
*/
