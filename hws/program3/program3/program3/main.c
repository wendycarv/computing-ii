/*
 Program: Number Filter
 Author: Wendy Carvalho
 Date:04/10/23
 Time spent: 4 hours
 Purpose: The purpose of this program is to filter numbers through an array, removing duplicates and ordering them from least to greatest.
 */

#include <stdio.h>
#include <stdlib.h>
#include "status.h"

//void list_insert(int array[], int num, int* counter);
void shell_sort(int array[], int counter);
void print_list(int array[], int counter);
void remove_duplicates(int array[], int* size);

int main(int argc, const char * argv[])
{
    int num;
    int counter = 0;
    int* pNumbers;
    
    pNumbers = (int*)malloc(sizeof(int));
    
    if (pNumbers == NULL)
    {
        printf("Failed to allocate dynamic array.\n");
        exit(1);
    }
    
    printf("Enter some numbers: \n");
    scanf("%d", &num);
    while (num != -1)
    {
        pNumbers[counter] = num;
        counter++;
        scanf("%d", &num);
    }
    
    remove_duplicates(pNumbers, &counter);
    shell_sort(pNumbers, counter);
    print_list(pNumbers, counter);
    
    return 0;
}

void remove_duplicates(int array[], int* size)
{
    int i, j, k;

    for (i = 0; i < *size; i++)
    {
        //comparing adjacent elements
        for (j = i + 1; j < *size;)
        {
            //if a duplicate is found
            if (array[j] == array[i])
            {
                //move everything down
                for (k = j; k < *size; k++)
                {
                    array[k] = array[k + 1];
                }
                (*size)--;
            }
            //otherwise, keep traversing through list
            else
            {
                j++;
            }
        }
    }
}
/*
void list_insert(int array[], int num, int* counter)
{
    int i = 0;
    int j = 0;
    int* temp;
    
    Boolean duplicate_found = FALSE;
    
    if (*counter == 1)
    {
        array[i] = num;
    }
    else
    {
        temp = (int*)malloc(sizeof(int));

        while (i < *counter - 1)
        {
            if (num != array[j])
            {
                temp[i] = array[j];
                i++;
                j++;
            }
            else
            {
                duplicate_found = TRUE;
                j++;
            }
        }
        if (duplicate_found == FALSE)
        {
            temp[i] = num;
        }

        array = temp;
    }
}
*/

void shell_sort(int array[], int counter)
{
    int i;
    int j;
    int temp;
    int h = 2;
    
    while (h < counter / 3)
    {
        h *= 2;
    }
    h--;
    
    while (h != 0)
    {
        for (i = h; i < counter; i++)
        {
            j = i;
            temp = array[j];
            
            while (j >= h && array[j - h] > temp)
            {
                array[j] = array[j - h];
                j -= h;
            }
            array[j] = temp;
        }
        h = h / 2;
    }
}

void print_list(int array[], int counter)
{
    int i;
    
    for (i = 0; i < counter; i++)
    {
        printf("%d\n", array[i]);
    }
}

/*
int main(int argc, const char * argv[])
{
    int i;
    QUEUE hQ;
    
    hQ = queue_init_default();
    if (hQ == NULL)
    {
        printf("Failed to allocate space for queue object.\n");
        exit (1);
    }
    
    for(i = 1; i <= 5; i++)
    {
        if(queue_insert(hQ, i) == FAILURE)
        {
            printf("Failed to insert item%d\n", i);
            exit(1);
        }
        
        while (!queue_is_empty(hQ))
        {
            printf("The front of the line is %d\n", queue_front(hQ, NULL));
            queue_service(hQ);
        }
    }
    queue_destroy(&hQ);
    return 0;
}
*/
