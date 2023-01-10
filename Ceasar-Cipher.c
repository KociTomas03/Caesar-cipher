/*
    Ceasar Cipher, where you don't have to care about your input being too long
    author: Tomas Koci
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define INCREMENT 20
#define SHIFT 3

/*
    In order to not face any troubles with input being too big I decided to have
    the value to dynamically increase in size. Should be more acceptable for users.
*/
typedef struct
{
    int length;
    int capacity;
    int *value;
} Tstr;

/*
    Loads string from stdin,
    returns true if we have loaded succesfully,
    false if we didn't manage to allocate enough memory
*/

bool load_string(Tstr *input)
{
    printf("Input your sentance: ");
    int c;
    while ((c = getc(stdin)) != EOF)
    {
        if (c != '\n')
        {

            if (input->length + 1 >= input->capacity)
            {
                input->value = realloc(input->value, sizeof(int) * (input->capacity + INCREMENT));
                if (input->value == NULL)
                {
                    return false;
                }
                input->capacity += INCREMENT;
            }
            input->value[input->length] = c;
            input->length++;
        }
    }
    input->value[input->length] = '\0';
    return true;
}

/*
    Transfers the msg to upper cahracters, just for the sake of convinience.
*/
void upperString(int *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = toupper(str[i]);
        i++;
    }
    return;
}

/*
    Encrypts the msg via Ceasar Cipher
*/
void encrypt(Tstr *val)
{
    upperString(val->value);
    int i = 0;
    while (val->value[i] != '\0')
    {
        if (val->value[i] >= 'A' && val->value[i] <= 'Z')
        {
            if ((val->value[i] - 'A' - SHIFT) % 26 >= 0)
            {
                val->value[i] = 'A' + ((val->value[i] - 'A' - SHIFT) % 26);
            }
            else
            {
                val->value[i] = 'Z' + 1 + ((val->value[i] - 'A' - SHIFT) % 26);
            }
        }
        i++;
    }
    return;
}

/*
    Since Tstr holds information about its length there's no need to be checking
    for '\0' in string.
*/
void print_string(Tstr output)
{
    for (int i = 0; i < output.length; i++)
    {
        printf("%c", output.value[i]);
    }
}

/*letting args in - maybe in future I'll utilize them*/
int main(int argc, char *argv[])
{
    Tstr input = {.length = 0, .capacity = INCREMENT, .value = malloc(sizeof(int) * INCREMENT)};

    if (load_string(&input))
    {
        encrypt(&input);

        print_string(input);
    }

    return 0;
}