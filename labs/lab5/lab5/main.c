#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "my_string.c" 
#include "generic_vector.h"
#include "tree.h"

#define MAX_WORD_LENGTH 30

ITEM integer_init_copy(ITEM hInt);
void integer_destroy(ITEM* phInt);
int prompt_user_word_length(void);
int prompt_user_guesses(void);
char get_character(void);
Boolean is_character_used(MY_STRING hString, char guess);
Boolean prompt_user_running_total(void);
Boolean prompt_user_replay(void);
void hangman(void);
void clear_keyboard_buffer(void);
GENERIC_VECTOR* init_dictionary(void);

int main(int argc, char* argv[])
{
    /*
    do{
        hangman();
    }while(prompt_user_replay());
    */
    char c;
    int i;
    
    MY_STRING string = my_string_init_c_string("The");
    MY_STRING new_key = my_string_init_default();
    MY_STRING word_family = my_string_init_default();
    
    
    for (i = 0; my_string_get_size(string); i++)
    {
        my_string_push_back(new_key, '-');
    }
    
    printf("Enter a guess: ");
    scanf("%c", &c);
    
    get_word_key_value(word_family, new_key, string, c);
    printf("The new key is: ");

    my_string_insertion(new_key, stdout);

    return 0;
}

void hangman(void)
{
    int word_length;
    int number_of_guesses;
    int i;
    int running_total;
    char guess;

    TREE hTree = tree_init_default();
    
    GENERIC_VECTOR *dictionary = init_dictionary();
    GENERIC_VECTOR largest_family = NULL;
        
    MY_STRING letter_guesses = my_string_init_c_string(" ");
    MY_STRING key = my_string_init_default();
    MY_STRING family = my_string_init_default();
  
    word_length = prompt_user_word_length();
    number_of_guesses = prompt_user_guesses();
    running_total = prompt_user_running_total();
    
    //make blanks of the word_length (coffee = ------)
    for (i = 0; i < word_length; i++)
    {
        my_string_push_back(key, '-');
    }
    
    //only let the user keep guessing if they still have guesses remaining
    while (number_of_guesses > 0)
    {
        //give them the current information they know
        printf("You have %d guess(es) remaining.\n", number_of_guesses);
        printf("Letters used:");
        my_string_insertion(letter_guesses, stdout);
        printf("Word:");
        my_string_insertion(key, stdout);
        
        //make sure user enters a letter they haven't guessed before
        do{
            guess = get_character();
        }
        while (is_character_used(key, guess));
        
        //add the user's letter guess to the guess_list
        my_string_push_back(letter_guesses, guess);
        my_string_push_back(letter_guesses, ',');
        my_string_push_back(letter_guesses, ' ');
        
        //look for all the possibilities of the letter in words of the word_length
        if (running_total == TRUE)
        {
            printf("The computer has %d possibilities remaining.\n", running_total);
        }
        
        // for each word of word_length length in dictionary[word_length], count how many times the guess appears
        for (i = 0; i < generic_vector_get_size(dictionary[word_length]); i++)
        {
            get_word_key_value(key, family, generic_vector_at(dictionary[word_length], i), guess);
            tree_push(hTree, family, generic_vector_at(dictionary[word_length], i));
        }
        
        largest_family = tree_get_largest_family(hTree, running_total);
        generic_vector_destroy(&(dictionary[word_length]));
        dictionary[word_length] = generic_vector_init_default(my_string_assignment_two, my_string_destroy);
        for (i = 0; i < generic_vector_get_size(largest_family); i++)
        {
            generic_vector_push_back( dictionary[word_length], generic_vector_at(largest_family, i));
        }

        get_word_key_value(key, family, generic_vector_at(dictionary[word_length], 0), guess);

        if (my_string_compare(key, family) == 0)
        {
            printf("\nIncorrect. The word does not include any %c's\n\n", number_of_guesses);
            number_of_guesses--;
        }

        my_string_assignment(&key, family);

        generic_vector_destroy(&largest_family);
        tree_destroy(&hTree);
        my_string_destroy(&family);
        family = my_string_init_default();
        hTree = tree_init_default();

        if (number_of_guesses == 0)
        {
            printf("You lose!\nThe word was: ");
            my_string_insertion(generic_vector_at(dictionary[word_length], 0), stdout);
            printf("\n\n");
            break;
        }

        if (my_string_compare(generic_vector_at(dictionary[word_length], 0), key) == 0)
        {
            //if there's only one word left
            if (generic_vector_get_size(dictionary[word_length]) == 1)
            {
                printf("You win!\nThe word was: ");
                my_string_insertion(generic_vector_at(dictionary[word_length], 0), stdout);
                printf("\n\n");
                break;
            }
        }
    }
    
    // free data
    tree_destroy(&hTree);
    my_string_destroy(&key);
    my_string_destroy(&letter_guesses);
    my_string_destroy(&family);
        
    for (i = 0; i < MAX_WORD_LENGTH; i++)
    {
        generic_vector_destroy(&dictionary[i]);
    }
        
    free(dictionary);
}

Status get_new_key(MY_STRING old_key, MY_STRING new_key, MY_STRING word, char guess)
{
    int i;
    
    //ensure new key is empty
    while (!my_string_empty(new_key))
    {
        my_string_pop_back(new_key);
    }
    
    //search the word
    for (i = 0; i < my_string_get_size(word); i++)
    {
        //here we're creating for example in the word wishing there are two 'i's, so it'd be -i--i---, while wistful would be -i-----. both keys are being added to the tree, but this function goes through one word possibility at a time
        if (*my_string_at(word, i) == guess)
        {
            if(!my_string_push_back(new_key, guess))
            {
                return FAILURE;
            }
        }
        else
        {
            if(!my_string_push_back(new_key, *my_string_at(old_key, i)))
            {
                return FAILURE;
            }
        }
    }
    
    return SUCCESS;
}

Boolean prompt_user_replay(void)
{
    char c ;
    printf("Would you like to play again? (y/n)\n");

    scanf("%c", &c);
    clear_keyboard_buffer();
    
    c = tolower(c);

    while (!isalpha(c))
    {
        printf("Please enter (y/n)\n");
        scanf("%c", &c);
        clear_keyboard_buffer();
    }

    if (c == 'y')
    {
        return TRUE;
    }
    
    if (c == 'n')
    {
        return FALSE;
    }
    
    return FALSE;
}
int prompt_user_word_length(void)
{
    int word_length;
    int noc;
    
    printf("How many letters would you like in the word?\n");
    noc = scanf("%d", &word_length);
    
    while (noc == 1 && (word_length > MAX_WORD_LENGTH || word_length <= 2))
    {
        printf("You can't guess a word of that size. Try a different word length: \n");
        noc = scanf("%d", &word_length);
    }
    
    return word_length;
}

int prompt_user_guesses(void)
{
    int guesses;
    int noc;
    
    printf("How many guesses would you like to have?\n");
    noc = scanf("%d", &guesses);
    
    while (noc == 1 && guesses == 0)
    {
        printf("You have to have at least one guess. Try a higher number: \n");
        noc = scanf("%d", &guesses);
    }
    
    return guesses;
}

Boolean prompt_user_running_total(void)
{
    char choice;
    printf("Would you like the running total of the number of words remaining in the word list? Type y for yes or n for no: \n");
    scanf("%c", &choice);
    
    while (choice != 'y' || choice != 'n')
    {
        printf("Type y for yes or n for no");
        scanf("%c", &choice);
    }
    
    if (isalpha(choice) && choice == 'y')
    {
        return TRUE;
    }
    else if (isalpha(choice) && choice == 'n')
    {
        return FALSE;
    }
    
    return FALSE;
}

char get_character(void)
{
    char c;
    
    printf("Enter guess:");
    scanf("%c", &c);
    clear_keyboard_buffer();
        
    while (!isalpha(c))
    {
        printf("Enter guess:");
        scanf("%c", &c);
        clear_keyboard_buffer();
    }
        
    return c;
}

Boolean is_character_used(MY_STRING letter_guesses, char guess)
{
    My_string* pString = (My_string*)letter_guesses;
    
    int i;
    
    for (i = 0; i < my_string_get_size(letter_guesses); )
    {
        if (guess == pString->data[i])
        {
            printf("You've already guessed that letter. Try again.\n");
            return TRUE;
        }
    }
    
    return FALSE;
}


GENERIC_VECTOR* init_dictionary(void)
{
    GENERIC_VECTOR *hVector = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * 30);
    MY_STRING hString = NULL;
    FILE* fp;
    int i;
    int string_size;
    
    char dictionary[] = "/Users/wendy/Documents/school/uml/spring 2023/comp ii lab/lab5/lab5/dictionary.txt";
    
    //fp = fopen("dictionary.txt", "r");
    fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        printf("Unable to open dictionary.txt\n");
        exit(1);
    }
    
    hString = my_string_init_default();
    if (hString == NULL)
    {
        printf("Failed to initialize string\n");
        exit(1);
    }
    
    //for 30
    for (i = 0; i < 30; i++)
    {
        hVector[i] = generic_vector_init_default(my_string_assignment_two,
        my_string_destroy);
        if (hVector[i] == NULL)
        {
            exit(1);
        }
    }
    
    while (my_string_extraction(hString, fp)) 
    {
        string_size = my_string_get_size(hString);
        
        //printf("String found: ");
        //my_string_insertion(hString, stdout);
        //printf("\n");
        
        if (string_size < 30)
        {
            if(!generic_vector_push_back(hVector[string_size], (ITEM)hString))
            {
                printf("Failed to push string of size %d from dictionary onto vector\n", string_size);
                exit(1);
            }
            //printf("Vector at words of size %d: ", string_size);
            //my_string_insertion(generic_vector_at(hVector[string_size], 0), stdout);
            //printf("\n");
        }
    }

    /*printf("Strings of size 3: \n");
    for (i = 0; i < my_string_get_size(hVector[3]); i++)
    {
        my_string_insertion(generic_vector_at(hVector[3], i), stdout);
        printf("\n");
    }
    */
    
    for (i = 0; i < 30; i++)
    {
        printf("Amount of words in Vector[%d]: %d\n", i, my_string_get_size(hVector[i]));
    }
               
    my_string_destroy(&hString);
    fclose(fp);
    
    return hVector;
}

ITEM integer_init_copy(ITEM hInt)
{
    int* pInt;
    int* pArg = (int*)hInt;
    pInt = (int*)malloc(sizeof(int));
    if (pInt != NULL)
    {
        *pInt = *pArg;
    }
    return pInt;
}

void integer_destroy(ITEM* phInt)
{
    int* pInt = (int*)*phInt;
    free(pInt);
    *phInt = NULL;
}

void clear_keyboard_buffer(void)
{
    char c;
    scanf("%c", &c);

    while (c != '\n')
    {
        scanf("%c", &c);
    }
    
    return;
}
