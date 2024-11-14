#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int number_of_assignments;
int number_of_comparisons;

void print_array(int numbers[], int size);

void bubble_sort(int numbers[], int size);
void selection_sort(int numbers[], int size);
void vanilla_insertion_sort(int numbers[], int size);
//void insertion_sort_with_shifting(int numbers[], int size);
//void insertion_sort(int numbers[], int size);

void heapify(int numbers[], int size);
void remove_max(int numbers[], int* pSize);
void fix_down(int numbers[], int size, int index);

int find_index_of_smallest(int numbers[], int size, int starting_index);

void reset_arrays(int numbers[], int backup[], int size);

void my_swap(int* a, int* b);

int main(int argc, const char * argv[])
{
    int* pNumbers;
    int* backup;
    int i;
    
    pNumbers = (int*)malloc(sizeof(int) * SIZE);
    
    if (pNumbers == NULL)
    {
        printf("Failed to allocate dynamic array.\n");
        exit(1);
    }
    
    backup = (int*)malloc(sizeof(int) * SIZE);
    
    if (backup == NULL)
    {
        printf("Failed to allocate backup dynamic array.\n");
        exit(1);
    }
        
    for (i = 0; i < SIZE; i++)
    {
        //pNumbers[i] = (rand() << 15) + rand(); // large random numbers
        pNumbers[i] = i;
        //pNumbers[i] = 1000 - i; // worst case, numbers are in reverse order
        
        backup[i] = pNumbers[i];
    }

    //print_array(pNumbers, SIZE);
    //*******************BUBBLE SORT**********************
    /*
    number_of_assignments = 0;
    number_of_comparisons = 0;
    bubble_sort(pNumbers, SIZE);
    printf("Bubble Sort DONE*******");
    printf("%d assignments and %d comparisons\n", number_of_assignments, number_of_comparisons);
    //print_array(pNumbers, SIZE);
    
    reset_arrays(pNumbers, backup, SIZE);
    */
    
    //*******************VANILLA INSERTION SORT**********************
    /*
    number_of_assignments = 0;
    number_of_comparisons = 0;
    vanilla_insertion_sort(pNumbers, SIZE);
    printf("Vanilla Insertion Sort DONE*******");
    printf("%d assignments and %d comparisons\n", number_of_assignments, number_of_comparisons);
     */
    
    //*******************INSERTION SORT WITH SHIFTING**********************
    number_of_assignments = 0;
    number_of_comparisons = 0;
    selection_sort(pNumbers, SIZE);
    printf("Insertion Sort DONE*******");
    printf("%d assignments and %d comparisons\n", number_of_assignments, number_of_comparisons);
    //print_array(pNumbers, SIZE);
    return 0;
}

void print_array(int numbers[], int size)
{
    int i;
    
    for (i = 0; i < size; i++)
    {
        printf("%d", numbers[i]);
    }
}

void bubble_sort(int numbers[], int size) //too many swaps
{
    int i;
    int j;
    int temp;
    int something_swaps;
    
    number_of_assignments++; // i init
    for(i = 0; i < size - 1; i++)
    {
        number_of_comparisons++; // i condition
        something_swaps = 0;
        number_of_assignments++; // something_swaps
        number_of_assignments++; // j init
        for(j = 0; j < size - 1 - i; j++)
        {
            number_of_comparisons++; //j condition
            number_of_comparisons++; //if
            if(numbers[j] > numbers[j+1])
            {
                my_swap(&numbers[j], &numbers[j+1]); //makes it slower
                something_swaps = 1;
                number_of_assignments++;
            }
            number_of_assignments++; // j increment
        }
        number_of_comparisons++; //last j condition
        if (!something_swaps) // you don't have to sort anything, so you can break
        {
            break;
        }
        number_of_assignments++; // i increment
    }
    number_of_comparisons++; //last i condition
}

void my_swap(int* a, int* b)
{
    int temp;
    number_of_assignments += 3;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*void bubble_sort(int numbers[], int size)
{
    int i;
    int j;
    int temp;
    int something_swaps;
    
    for(i = 0; i < size - 1; i++)
    {
        something_swaps = 0;
        for(j = 0; j < size - 1 - i; j++)
        {
            if(numbers[j] > numbers[j+1])
            {
                //my_swap(&numbers[j], &numbers[j+1]); //makes it slower
                something_swaps = 1;
            }
        }
        if (!something_swaps) // you don't have to sort anything, so you can break
        {
            break;
        }
    }
    
}
 */

void reset_arrays(int numbers[], int backup[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        numbers[i] = backup[i];
    }
}

void selection_sort(int numbers[], int size) //for every element of the array except the last, we look all the elements of the array that are unsorted, and swap the smallest to the beginning of the unsorted portion, then advance the list so you ignore the beginning, then you do it again
{
    int i;
    int index_of_smallest;
    number_of_assignments++; // i init for the for loop
    for(i = 0; i < size - 1; i++)
    {
        number_of_comparisons++; // i condition
        index_of_smallest = find_index_of_smallest(numbers, size, i);
        number_of_assignments++; //function call

        my_swap(&numbers[i], &numbers[index_of_smallest]);
        number_of_assignments++; // increment
    }
    number_of_comparisons++; // last i condition
}

int find_index_of_smallest(int numbers[], int size, int starting_index) //assume the first element is the is the smallest, and if you're wrong, switch it, otherwise you prove yourself right
{
    int index_of_smallest = starting_index;
    int i;
    
    number_of_assignments++; // init index
    number_of_assignments++; // i init
    for (i = starting_index + 1; i < size; i++) // +1 because you're already assuming that the starting_index is the smallest, so you need to check the adjacent element
    {
        number_of_comparisons++; //condition
        number_of_comparisons++; //if statement
        if(numbers[i] < numbers[index_of_smallest]) // then you were wrong!
        {
            index_of_smallest = i;
            number_of_assignments++; //body
        }
        number_of_assignments++; //increment
    }
    number_of_comparisons++; //last condition
    
    return index_of_smallest;
}

void vanilla_insertion_sort(int numbers[], int size) //goes thru the list, ignoring the first element, takes every element and pulls it to the left, swapping it to the left until it's in the correct positiong
{
    int i;
    int j;
    number_of_assignments++; //i init
    
    for (i = 1; i < size; i++) //ignore 0th element because it's already sorted
    {
        number_of_comparisons++; //condition
        j = i;
        number_of_assignments++; //init j
        while(j > 0 && numbers[j-1] > numbers[j]) //while there's a left neighbor, then you have something in bounds, and while you're supposed to swap (while value to left is bigger)
        {
            number_of_comparisons+=2; //two conditions to be true to enter the while loop
            my_swap(&numbers[j], &numbers[j-1]);
            j--;
            number_of_assignments++; //decrement
        }
        if (j <= 0) //then it short-circuited
        {
            number_of_comparisons++;
        }
        else
        {
            number_of_comparisons += 2;
        }
        number_of_assignments++; //increment
    }
    number_of_comparisons++; //last condition
}

void insertion_sort_with_shifting(int numbers[], int size)
{
    int i;
    int j;
    int temp;
    
    for (i = 1; i < size; i++)
    {
        j = i;
        temp = numbers[j];
        while(j > 0 && numbers[j-1] > temp)
        {
            numbers[j] = numbers[j-1];
            j--;
        }
        numbers[j] = temp;
    }
}


void insertion_sort(int numbers[], int size)
{
    int i;
    int j;
    int temp;
    int index_of_smallest;
    
    number_of_assignments++; //function call
    
    index_of_smallest = find_index_of_smallest(numbers, size, 0); //puts the sentinel value in the correct position
    my_swap(&numbers[0], &numbers[index_of_smallest]);
     
    number_of_assignments++; //i init
    for (i = 2; i < size; i++) //don't need to start at 1 bc it's already in the correct position
    {
        number_of_comparisons++; //condition
        j = i;
        temp = numbers[j];
        number_of_comparisons++; //condition
        number_of_assignments += 2; //stuff

        while (j > 0 && numbers[j-1] > temp)
        {
            number_of_comparisons++; //condition
            numbers[j] = numbers[j-1];
            j--;
            number_of_assignments += 2; //body
        }
        number_of_comparisons++; //last condition
        numbers[j] = temp;
        number_of_assignments++; //completing the shift
        number_of_assignments++; //increment
    }
    number_of_comparisons++; //last condition
}

void shell_sort(int numbers[], int size)
{
    int h = 2;
    int i;
    int j;
    int temp;
    
    while (h < size / 3)
    {
        number_of_comparisons++; // condition of while loop
        h *= 2;
        number_of_assignments++; //h modification
    }
    number_of_comparisons++; // last condition
    h--;
    number_of_assignments++; //h modification
    
    while (h != 0)
    {
        number_of_comparisons++; //condition
        number_of_assignments++; //i init;
        for (i = h; i < size; i++)
        {
            number_of_comparisons++; //condition
            j = i;
            temp = numbers[j];
            number_of_assignments += 2; //stuff
            while (j >= h && numbers[j - h] > temp)
            {
                number_of_comparisons += 2;
                numbers[j] = numbers[j - h];
                j -= h;
                number_of_assignments += 2; //body
            }
            if (j < h)
            {
                number_of_comparisons++;
            }
            else
            {
                number_of_comparisons += 2;
            }
            numbers[j] = temp;
            number_of_assignments++; //completing the shift
            number_of_assignments++; //increment
        }
        number_of_comparisons++; //condition
        h = h / 2;
        number_of_assignments++; //decrease h
    }
    number_of_comparisons++; //last condition
}

void heap_sort(int numbers[], int size)
{
    int i;
    int iterations = size - 1;
    heapify(numbers, size);
    for (i = 0; i < iterations; i++)
    {
        remove_max(numbers, &size);
        
    }
}

void heapify(int numbers[], int size)
{
    int i;
    
    for (i = size/2 - 1; i >= 0; i--)
    {
        fix_down(numbers, size, i);
    }
}

void remove_max(int numbers[], int* pSize)
{
    //swap with last
    my_swap(&numbers[0], &numbers[*pSize - 1]);
    (*pSize)--;
    fix_down(numbers, *pSize, 0);
    //decrease the size
    //call fix down on the root
    
}
                                  
void fix_down(int numbers[], int size, int index)
{
    int index_of_left_child;
    int index_of_right_child;
    int index_of_largest_child;
    
    number_of_assignments += 2;
    index_of_left_child = index * 2 + 1;
    index_of_right_child = index * 2 + 2;
    
    number_of_comparisons++; //if
    if (index_of_left_child < size)
    {
        number_of_comparisons++; //if
        if(index_of_right_child < size) //here we're determing which child has the largest value to then compare it to the parent
        {
            number_of_assignments++; //ternary
            number_of_comparisons++; //ternary operator
            index_of_largest_child =
                (numbers[index_of_left_child] > numbers[index_of_right_child])?
            index_of_left_child : index_of_right_child; // is the heap at the index of the left child bigger than the one at the right child this, then (:) the left is bigger.....
        }
        else
        {
            number_of_assignments++; //largest child
            index_of_largest_child = index_of_left_child;
        }
        number_of_comparisons++; //if
        if (numbers[index] > numbers[index_of_largest_child])
        {
            my_swap(&numbers[index], &numbers[index_of_largest_child]);
            fix_down(numbers, size, index_of_largest_child);
        }
    }
}

void quick_sort(int numbers[], int size)
{
    //select a pivot ... performs better when you have an item in the middle (select three items at random, compare them and take the MEDIAN of the three)
    
    //partition the list into two segments by scanning
    
    int index_of_left = 0;
    int index_of_right = size - 1;
    
    while(index_of_left < index_of_right)
    {
        //scan from right
        while(index_of_left < index_of_right && numbers[index_of_right] >= numbers[0])
        {
            index_of_right--;
        }
        
        //scan from left
        while (index_of_left < index_of_right && numbers[index_of_left] >= numbers[0])
        {
            index_of_left++;
        }
        
        if(index_of_left < index_of_right)
        {
            my_swap(&numbers[index_of_left], &numbers[index_of_right]);
        }
    }
    
    my_swap(&numbers[0], &numbers[index_of_left]); // if the indexes are the same
    
    //sort left half
    if (index_of_left > 1) //if the size is big enough, sort the left half
    {
        quick_sort(numbers, index_of_left); //you're passing in the beginning of the array to work with
    }
    

    //sort right half
    if (size - index_of_left - 1 > 1) //if there are elements to sort, then quick sort them
    {
        quick_sort(&numbers[index_of_left + 1], size - index_of_left - 1); //the 1 is the pivot
    }
}

void random_pivot_quick_sort(int numbers[], int size)
{
    //select a pivot
    
    int selected_pivot = ((rand() << 15) + rand()) % size;
    
    my_swap(&numbers[0], &numbers[selected_pivot]);
    
    int index_of_left = 0;
    int index_of_right = size - 1;
    
    while (index_of_left < index_of_right)
    {
        number_of_comparisons++; //condition
        
    }
                          
                          
}
void better_pivot_quick_sort(int numbers[], int size)
{
    //select a pivot ... performs better when you have an item in the middle (select three items at random, compare them and take the MEDIAN of the three)
    
    //partition the list into two segments by scanning
    
    int leftmost_element_index = 0;
    int rightmost_element_index = size - 1;
    int middle_element_index = size / 2;
    
    int index_of_left = 1;
    int index_of_right = size - 1;
    
    if (numbers[rightmost_element_index] < numbers[leftmost_element_index])
    {
        my_swap(&numbers[leftmost_element_index], &numbers[rightmost_element_index]);
    }
    
    if (numbers[rightmost_element_index] < numbers[middle_element_index])
    {
        my_swap(&numbers[rightmost_element_index], &numbers[middle_element_index]);
    }
        
    while(index_of_left < index_of_right)
    {
        //scan from right
        while(index_of_left < index_of_right && numbers[index_of_right] >= numbers[0])
        {
            index_of_right--;
        }
        
        //scan from left
        while (index_of_left < index_of_right && numbers[index_of_left] >= numbers[0])
        {
            index_of_left++;
        }
        
        if(index_of_left < index_of_right)
        {
            my_swap(&numbers[index_of_left], &numbers[index_of_right]);
        }
    }
    
    my_swap(&numbers[0], &numbers[index_of_left]); // if the indexes are the same
    
    //sort left half
    if (index_of_left > 1) //if the size is big enough, sort the left half
    {
        quick_sort(numbers, index_of_left); //you're passing in the beginning of the array to work with
    }
    

    //sort right half
    if (size - index_of_left - 1 > 1) //if there are elements to sort, then quick sort them
    {
        quick_sort(&numbers[index_of_left + 1], size - index_of_left - 1); //the 1 is the pivot
    }
}
