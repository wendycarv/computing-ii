#ifndef generic_h
#define generic_h

typedef void* ITEM;

struct generic_vector
{
    int size;
    int capacity;
    ITEM* data;
    void (*assignment)(ITEM* pLeft,ITEM hRight);
    void (*destroy)(ITEM*);
};

typedef struct generic_vector Generic_vector;

#endif 
