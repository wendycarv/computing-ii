#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
