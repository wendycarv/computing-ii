#include <stdio.h>
#include <stdlib.h>
#include "date.h"

struct date // Known type (this file is the only file that should know what a date really is)
{
    int month;
    int day;
    int year;
};

typedef struct date Date;

DATE date_init_default(void)
{
    Date* pDate = (Date*)malloc(sizeof(Date));
    
    if (pDate != NULL)
    {
        pDate->month = 1;
        pDate->day = 1;
        pDate->year = 1970;
    }
    return (DATE)pDate;
}
void date_output(DATE hDate)
{
    Date* pDate = (Date*)hDate; // casting to the known type
    
    printf("%d/%d/%d", pDate->month, (*pDate).day, pDate->year);
}

int date_get_day(DATE hDate)
{
    Date* pDate = (Date*)hDate; //casting to the known type
    return pDate->day;
}

int date_get_month(DATE hDate)
{
    Date* pDate = (Date*)hDate; //casting to the known type
    return pDate->month;
}

int date_get_year(DATE hDate)
{
    Date* pDate = (Date*)hDate; //casting to the known type
    return pDate->year;
}

char* date_get_month_name(DATE hDate)
{
    Date* pDate = (Date*)hDate; //casting to the known type
    switch(pDate->month)
    {
        case 1:
            return "January";
        case 2:
            return "February";
        default:
            return "Invalid Month Name";
    }
}

void date_destroy(DATE* phDate)
{
    Date* pDate = (Date*)*phDate; // casting to the known type
    free(pDate);
    *phDate = NULL;
}
