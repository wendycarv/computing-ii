#include <stdio.h>
#include <stdlib.h>

#define SIZE (7) //macro for size

/*
void say_hello(void);

void say_hola(void);

void say_oi(void);

void say_bonjour(void);

void say_ni_hao(void);

void say_salam(void);

void say_greeting(void (*greeting)(void));
*/

void bubble_sort(int numbers[], int size, int (*compare)(int, int));

int less_than(int a, int b);

int greater_than(int a, int b);

int odd_compare(int a, int b);

int main(int argc, const char * argv[])
{
    int (*compare)(int, int);
    
    int numbers[SIZE];
    int i;
    
    for (i = 0; i < SIZE; i++)
    {
        numbers[i] = rand();
    }
    
    for (i = 0; i < SIZE; i++)
    {
        printf("%d\n", numbers[i]);
    }
    
    printf("******\n");
    
    bubble_sort(numbers, SIZE, less_than);

    for (i = 0; i < SIZE; i++)
    {
        printf("%d\n", numbers[i]);
    }
    
    /*
    void (*greeting)(void);
    greeting = say_salam;
     */
    
    /*
     void (*say_hello)(void);
     say_greeting(say_bonjour);
     */
   
    /*
    int i;

    void (*bunch_of_greetings[])(void) = {
        say_hello,
        say_hola,
        say_ni_hao,
        say_bonjour,
        say_salam,
        say_oi,
    };
    
    for (i = 0; i < sizeof(bunch_of_greetings) / sizeof(*bunch_of_greetings); i++) //*bunch_of_greetings is the first element so = bunch_of_greetings[0]
    {
        bunch_of_greetings[i]();
    }
    */
    
    return 0;
}

void bubble_sort(int numbers[], int size, int (*compare)(int, int))
{
    int i;
    int j;
    for (i = 0; i < size - 1; i++) //do something n - 1 times
    {
        for (j = 0; j < size - 1 - i; j++) // keep j within bounds // after i iterations you can ignore i+1 items
        {
            //if (numbers[j] > numbers[j + 1]
            if (less_than(numbers[j + 1], numbers[j]))
            {
                int temp;
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }
}
                
int less_than(int a, int b)
{
    return a < b;
}

int greater_than(int a, int b)
{
    return a > b;
}

int odd_compare(int a, int b)
{
    if(a % 2 == b % 2) // if both are even or if both are odd
    {
        return a < b;
    }

    return a % 2;
    
}
/*
 void say_hello(void)
{
    printf("Hello!\n");
}

void say_hola(void)
{
    printf("Hola!\n");
}

void say_oi(void)
{
    printf("Oi!\n");
}

void say_bonjour(void)
{
    printf("Bonjour!\n");
}

void say_ni_hao(void)
{
    printf("Ni Hao!\n");
}

void say_salam(void)
{
    printf("Salam!\n");
}

void say_greeting(void (*greeting)(void))
{
    greeting();
}
*/
