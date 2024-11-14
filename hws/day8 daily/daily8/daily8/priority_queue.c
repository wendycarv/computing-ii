#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

typedef struct{
    int key;
    int value;
} Pair;

typedef struct {
    int capacity;
    int size;
    Pair* data;
}Heap;


static Boolean priority_queue_isFull(PRIORITY_QUEUE hQueue);
static Status priority_queue_increaseSize(PRIORITY_QUEUE hQueue);
static Pair priority_queue_createPair(int key, int value);
static void priority_queue_fix_down(Heap* queue, int index);
static void priority_queue_fix_up(Heap* queue, int index);

PRIORITY_QUEUE priority_queue_init_default(void) {
    Heap* newHeap = (Heap*) malloc(sizeof(Heap));
    if (newHeap != NULL) {
        newHeap ->size = 0;
        newHeap ->capacity = 1;
        newHeap ->data = (Pair*) calloc(sizeof(Pair), newHeap ->capacity);
        if (newHeap ->data == NULL) {
            free(newHeap);
            return NULL;
        }
    }
    return newHeap;
}

Boolean priority_queue_isFull(PRIORITY_QUEUE hQueue) {
    Heap* queue = (Heap*)hQueue;
    if (queue ->size >= queue ->capacity) return TRUE;
    return FALSE;
}

#define LOAD_FACTOR (2)
Status priority_queue_increaseSize(PRIORITY_QUEUE hQueue) {
    Heap* queue = (Heap*)hQueue;
    Pair* biggerData = (Pair*) calloc(sizeof(Pair),(queue ->capacity * LOAD_FACTOR));
    if (biggerData == NULL) {
        return FAILURE;
    }
    for (int i = 0; i < queue ->size; i++) {
        biggerData[i] = queue ->data[i];
    }
    free(queue ->data);
    queue ->data = biggerData;
    queue ->capacity *= LOAD_FACTOR;
    return SUCCESS;
}

Pair priority_queue_createPair(int key, int value) {
    Pair newPair;
    newPair.key = key;
    newPair.value = value;
    return newPair;
}

void priority_queue_fix_down(Heap* queue, int index) {
    int left_index = (index * 2) + 1;
    int right_index = (index * 2) + 2;
    int larger_index = index;
    
    if (left_index < queue ->size) {
        larger_index = queue ->data[left_index].key > queue ->data[larger_index].key ? left_index : larger_index;
    }
    if (right_index < queue ->size) {
        larger_index = queue ->data[right_index].key > queue ->data[larger_index].key ? right_index : larger_index;
    }
    if (larger_index == index) {
        return;
    }
    Pair temp = queue ->data[larger_index];
    queue ->data[larger_index] = queue ->data[index];
    queue ->data[index] = temp;
    priority_queue_fix_down(queue, larger_index);
}

void priority_queue_fix_up(Heap* queue, int index) {
    if (index == 0) return;
    int parent_index = (index - 1) / 2;
    if (queue ->data[index].key > queue ->data[parent_index].key) {
        Pair temp = queue ->data[index];
        queue ->data[index] = queue ->data[parent_index];
        queue ->data[parent_index] = temp;
        priority_queue_fix_up(queue, parent_index);
    }
    return;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue) {
    Heap* queue = (Heap*)hQueue;
    if (queue ->size <= 0) return TRUE;
    return FALSE;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item) {
    if (priority_queue_isFull(hQueue)) {
        if (priority_queue_increaseSize(hQueue) == FAILURE) {
            return FAILURE;
        }
    }
    Heap* queue = (Heap*)hQueue;
    Pair toInsert = priority_queue_createPair(priority_level, data_item);
    if (priority_queue_is_empty(hQueue)) {
        queue ->data[queue ->size++] = toInsert;
    }
    else {
        queue ->data[queue ->size] = toInsert;
        priority_queue_fix_up(queue, queue ->size);
        queue ->size++;
    }
    return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue) {
    if (priority_queue_is_empty(hQueue)) return FAILURE;
    
    Heap* queue = (Heap*)hQueue;
    Pair temp = queue ->data[queue ->size - 1];
    queue ->data[queue ->size - 1] = queue ->data[0];
    queue ->data[0] = temp;
    queue ->size--;
    priority_queue_fix_down(queue, 0);
    
    return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus) {
    if (pStatus == NULL) {
        if (priority_queue_is_empty(hQueue)) {
            return 0xC0FFEE;
        }
    }
    else {
        if (priority_queue_is_empty(hQueue)) {
            *pStatus = FAILURE;
            return 0xC0FFEE;
        }
    }
    Heap* queue = (Heap*)hQueue;
    return queue ->data[0].value;
}

void priority_queue_print(PRIORITY_QUEUE hQueue) {
    if (priority_queue_is_empty(hQueue)) {
        printf("[EMPTY]\n");
        return;
    }
    Heap* queue = (Heap*)hQueue;
    printf("[");
    for (int i = 0; i < queue ->size; i++) {
        if (i == queue ->size - 1) {
            printf("{%d:%d}]\n", queue ->data[i].key, queue ->data[i].value);
        }
        else printf("{%d:%d}, ", queue ->data[i].key, queue ->data[i].value);
    }
    return;
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue) {
    if (!priority_queue_is_empty(*phQueue)) {
        Heap* queue = (Heap*)*phQueue;
        free(queue ->data);
    }
    free(*phQueue);
    *phQueue = NULL;
    return;
}
