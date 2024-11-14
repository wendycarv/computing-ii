#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic.h"

struct my_string //Known type
{
  int size;
  int capacity;
  char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
  My_string* pString = (My_string*)malloc(sizeof(My_string));

  if (pString != NULL)
  {
    pString->size = 0;
    pString->capacity = 7;
    pString->data = (char*)malloc(sizeof(char*)*pString->capacity);

    if(pString->data == NULL)
    {
      free(pString);
      return NULL;
    }
  }

  return pString;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
    My_string* pString = (My_string*)malloc(sizeof(My_string));
    int i;

    if(pString !=NULL)
    {
      pString->size = 0;
      while(c_string[pString->size] != '\0')
        {
          pString->size++;
        }
      pString->capacity = pString->size + 1;
      pString->data = (char*)malloc(sizeof(char*)*pString->capacity);

      if (pString->data == NULL)
        {
          free(pString);
          return NULL;
        }

      for(i = 0; i<pString->size; i++)
        {
          pString->data[i] = c_string[i];
        }
    }
    return pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;
    return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
My_string* pString = (My_string*)hMy_string;
return pString->size;
}

int my_string_compare (MY_STRING hLeft_string, MY_STRING hRight_string)
{
    My_string* pLeft = (My_string*)hLeft_string;
    My_string* pRight = (My_string*)hRight_string;

      int i = 0;

    if (pLeft == NULL || pRight == NULL)
    {
        return 0;
    }
    
      while (i<pLeft->size && i<pRight->size && pLeft->data[i] == pRight->data[i])
      {
        i++;
      }

      if(i < pLeft->size && i < pRight->size && pLeft->data[i] != pRight->data[i])
      {
        return pLeft->data[i] - pRight->data[i];
      }

      return pLeft->size - pRight->size;
    
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string* pString = (My_string*)hMy_string;

  int noc;
  int c;
  int i;
  char first_character;
  char* temp;

  pString->size = 0;

  noc = fscanf(fp, "%c", &first_character);
    while (first_character == '\n')
    {
        noc = fscanf(fp, "%c", &first_character);
    }
    
  if (noc != 1)
    {
      return FAILURE;
    }

  pString->data[pString->size] = first_character;
  pString->size++;

  c = fgetc(fp);

  while (c != EOF && !isspace(c))
  {
    if (pString->size >= pString->capacity)
    {
      temp = (char*)malloc(sizeof(char) * pString->capacity *2);
      if (temp == NULL)
      {
          return FAILURE;
      }
      for (i = 0; i<pString->size; i++)
      {
          temp[i] = pString->data[i];
            }
            free(pString->data);
            pString->data = temp;
            pString->capacity *= 2;
          }

          pString->data[pString->size] = c;
          pString->size++;
          c = fgetc(fp);
        }

        if (c != EOF)
          {
            ungetc(c, fp);
          }

        return SUCCESS;
}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
    My_string* pString = (My_string*)hMy_string;

    int i;

    for (i = 0; i<pString->size; i++)
    {
        if (fputc(pString->data[i], fp) == EOF)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
    
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
    My_string* pString = (My_string*)hMy_string;
    char* temp;

    int i;

    if (pString->size >= pString->capacity) //if there's not enough room, make room
    {
        temp = (char*)malloc(sizeof(char) * pString->capacity * 2);
        if (temp == NULL)
        {
        return FAILURE;
        }
        
    for (i = 0; i < pString->size; i++)
      {
        temp[i] =  pString->data[i];
      }
    free(pString->data);
    pString->data = temp;
    pString->capacity *= 2;
  }

pString->data[pString->size] = item;
pString->size++;

return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;

    if (my_string_empty(hMy_string))
    {
        return FAILURE;
    }

    pString->size--;

    return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
    My_string* pString = (My_string*)hMy_string;

    if (index > pString->size || index < 0)
    {
        return NULL;
    }

    return &(pString->data[index]);
}

char* my_string_c_str(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;
    
    if (my_string_push_back(hMy_string, '\0') == FAILURE)
    {
        return NULL;
    }
    
    pString->size--;
    return pString->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*)hResult;
  My_string* pAppend = (My_string*)hAppend;

  char* temp;
  int i;

  if (pResult->capacity < (pResult->size + pAppend->size))
    {
      temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size + 1));

      if (temp == NULL)
        {
          return FAILURE;
        }

      for (i = 0; i < pResult->size; i++)
        {
          temp[i] = pResult->data[i];
        }
      free(pResult->data);
      pResult->data = temp;
      pResult->capacity = pResult->size + pAppend->size + 1;
    }

  for (i = 0; i < pAppend->size; i++)
    {
      pResult->data[pResult->size] = pAppend->data[i];
      pResult->size++;
    }

  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;

  return (Boolean)(pString->size <= 0);
}


Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight)
{
  My_string* pLeft = (My_string*)hLeft;
  My_string* pRight = (My_string*)hRight;

  int i;
  char* temp;

  if (pLeft->size < pRight->size)
    {
      temp = (char*)malloc(sizeof(char) * pRight->size);

      if (temp == NULL)
        {
          return FAILURE;
        }

      for (i = 0; i < pRight->size; i++)
        {
            if (pRight->data[i] != '\0')
            {
                temp[i] = pRight->data[i];
            }
        }
        temp[i] = '\0';
        free(pLeft->data);
        pLeft->data = temp;
        pLeft->size = pRight->size;
    }

  else
    {
      for (i = 0; i < pRight->size; i++)
        {
            if (pRight->data[i] != '\0')
            {
                pLeft->data[i] = pRight->data[i];
            }
        }
        pLeft->size = pRight->size;
        pLeft->data[i] = '\0';
    }

  return SUCCESS;

}

void my_string_assignment_two(MY_STRING* pLeft, MY_STRING hRight)
{
  My_string* pLeft_string = (My_string*)*pLeft;
  My_string* pRight_string = (My_string*)hRight;
 
  int i;
  char* temp;
  temp = my_string_c_str((MY_STRING)hRight);
 
  if(pLeft_string == NULL)
    {
      pLeft_string = my_string_init_c_string(temp);
    }
 
  else
    {
      pLeft_string->size = 0;
      for(i=0; i<pRight_string->size+1; i++)
        {
          my_string_push_back(pLeft_string, pRight_string->data[i]);
        }
    }
  *pLeft = pLeft_string;
}


MY_STRING my_string_init_copy(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;
    My_string* pString_copy = (My_string*)malloc(sizeof(My_string));

  int i;

  if (pString_copy != NULL)
  {
    pString_copy->size = pString->size;
    pString_copy->capacity = pString->capacity;
    pString_copy->data = (char*)malloc(sizeof(char) * pString_copy->capacity);

    if(pString_copy->data == NULL)
    {
      free(pString_copy);
      return NULL;
    }

    for (i = 0; i < pString->size; i++)
      {
          if (pString->data[i] != '\0')
          {
              pString_copy->data[i] = pString->data[i];
          }
      }
      pString_copy->data[i] = '\0';
  }

  return (MY_STRING)pString_copy;
}

void my_string_swap(MY_STRING hLeft, MY_STRING hRight)
{
    MY_STRING hLeft_copy = NULL;
    hLeft_copy = my_string_init_default();
    hLeft_copy = my_string_init_copy(hLeft);

    my_string_assignment(hLeft, hRight);
    my_string_assignment(hRight, hLeft_copy);

    my_string_destroy(&hLeft_copy);
}

//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
//   upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
    int i;
    int word_size;
    char letter;
    
    word_size = my_string_get_size(word);
    
    //while the guess key isn't empty, empty it
    while (!my_string_empty(new_key))
    {
        my_string_pop_back(new_key);
    }
    
    for (i = 0; i < word_size; i++)
    {
        //if the letter guessed is a letter at any place in the word, then use letter as a placeholder for the guess
        if (*my_string_at(word, i) == guess)
        {
            letter = guess;
        }
        // otherwise the letter is just gonna be a dash (-)
        else
        {
            letter = *my_string_at(current_word_family, i);
        }
        
        //place the letter variable, either a correctly guessed letter or just a dash onto the key
        if (!my_string_push_back(new_key, letter))
        {
            return FAILURE;
        }
    
    }
    
    return SUCCESS;
}

Boolean is_character_used(MY_STRING letter_guesses, char guess)
{
    My_string* pString = (My_string*)letter_guesses;
    
    int i;
    
    for (i = 0; i < my_string_get_size(letter_guesses); i++)
    {
        if (guess == pString->data[i])
        {
            printf("You've already guessed that letter. Try again.\n");
            return TRUE;
        }
    }
    
    return FALSE;
}


void my_string_destroy(MY_STRING* phString)
{
  My_string* pString = (My_string*)*phString;

  free(pString->data);
  free(pString);
    
    *phString = NULL;
}



