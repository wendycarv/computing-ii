/*
 Author: Wendy Carvalho
 Date: 04/06/2023
 Time spent: 2 hours
 Purpose of program: The purpose of this program is to create a priority queue using a heap.
*/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
int main(int argc, const char * argv[]) {
    PRIORITY_QUEUE test = priority_queue_init_default();
    
    for (int i = 0; i < 10; i++) {
        priority_queue_insert(test, i, i);
    }
    
    priority_queue_print(test);
    
    for (int i = 0; i < 10; i++) {
        printf("%d\n", priority_queue_front(test, NULL));
        priority_queue_service(test);
    }
    
    priority_queue_destroy(&test);
    return 0;
}
