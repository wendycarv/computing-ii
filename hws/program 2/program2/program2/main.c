#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int main(int argc, const char * argv[])
{
    int test_cases;
    int i;
    
    Node* trips = NULL;

    scanf("%d", &test_cases);
    
    for (i = 0; i < test_cases; i++)
    {
        test_case(&trips);
    }
    
    print_list(trips);

    destroy_node(trips); trips = NULL;
    
    return 0;
}

