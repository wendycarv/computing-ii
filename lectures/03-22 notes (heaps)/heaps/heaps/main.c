#include <stdio.h>

void fix_up(int heap[], int index);
void heap_insert(int heap[], int* pSize, int value);
void heap_remove_max(int heap[], int* pSize);
void fix_down(int heap[], int size, int index);

int main(int argc, const char * argv[])
{
    int heap[50];
    int size = 0;
    int i;
    
    for (i = 1; i <= 10; i++)
    {
        heap_insert(heap, &size, i);
    }

    for (i = 0; i < size; i++)
    {
        printf("%d\n", heap[i]);
    }
    
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", heap[0]);
        heap_remove_max(heap, &size);
    }
    
    printf("****\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", heap[i]);
        heap_remove_max(heap, &size);
    }
    
    return 0;
}

void heap_insert(int heap[], int* pSize, int value)
{
    heap[*pSize] = value; //putting it at that specific index
    fix_up(heap, *pSize); //needs to know where to start, so it starts at *pSize, making sure it's still a heap
    (*pSize)++;
}

void fix_up(int heap[], int index)
{
    int index_of_parent;
    int temp;
    
    if (index > 0) // then it has a parent, otherwise you'd do nothing
    {
        index_of_parent = (index - 1) / 2;
        if (heap[index] > heap[index_of_parent])
        {
            temp = heap[index];
            heap[index] = heap[index_of_parent];
            heap[index_of_parent] = temp;
            fix_up(heap, index_of_parent);
        }
    }
}

void heap_remove_max(int heap[], int* pSize)
{
    int temp;
    temp = heap[0];
    heap[0] = heap[*pSize - 1]; //swapping the root with the last element
    heap[*pSize - 1] = temp;
    
    (*pSize)--; //removing that value that was the root
    
    fix_down(heap, *pSize, 0);
}

void fix_down(int heap[], int size, int index)
{
    int index_of_left_child;
    int index_of_right_child;
    int index_of_largest_child;
    int temp;

    index_of_left_child = index * 2 + 1;
    index_of_right_child = index * 2 + 2;
    
    if (index_of_left_child < size)
    {
        if(index_of_right_child < size) //here we're determing which child has the largest value to then compare it to the parent
        {
            index_of_largest_child =
                (heap[index_of_left_child] > heap[index_of_right_child])?
            index_of_left_child : index_of_right_child; // is the heap at the index of the left child bigger than the one at the right child this, then (:) the left is bigger.....
        }
        else
        {
            index_of_largest_child = index_of_left_child;
        }
        
        if (heap[index_of_largest_child] > heap[index])
        {
            temp = heap[index];
            heap[index] = heap[index_of_largest_child];
            heap[index_of_largest_child] = temp;
            fix_down(heap, size, index_of_largest_child);
        }
    }

}
