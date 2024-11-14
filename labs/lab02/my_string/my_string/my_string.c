#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct my_string
{
  int size;
  int capacity;
  int* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
    My_string* pString = (My_string*) malloc(sizeof(My_string));

    if (pString != NULL)
    {
        pString->size = 0;
        pString->capacity = 1;
        pString->data = (int*)malloc(sizeof(int*)*pString->capacity);
      
        if(pString->data == NULL)
        {
            free(pString);
            return NULL;
        }
    }

    return pString;
}

int main(int argc, char* argv[])
{
    MY_STRING hMy_string = NULL;

    hMy_string = my_string_init_default();

    my_string_destroy(&hMy_string);

    return 0;
}

void my_string_destroy(MY_STRING* phString)
{
    My_string* pString = (My_string*)*phString;

    free(pString->data);
    free(pString);
    *phString = NULL;
    printf("Destroyification complete!\n");
}


