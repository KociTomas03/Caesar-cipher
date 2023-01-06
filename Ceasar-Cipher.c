#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define INCREMENT 20
#define SHIFT 3

typedef struct
{
    int length;
    int capacity;
    int *value;
} Tstr;

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
                    printf("sike");
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
            // printf("%d \n", 'A' + ((val->value[i] - 'A' - SHIFT) % 26));
        }
        i++;
    }
    return;
}

void print_string(Tstr output)
{
    for (int i = 0; i < output.length; i++)
    {
        printf("%c", output.value[i]);
    }
    /*int i = 0;
    while (output.value[i] != '\0')
    {
        printf("%c", output.value[i]);
        i++;
    }*/
}

int main(int argc, char *argv[])
{
    Tstr input = {.length = 0, .capacity = INCREMENT, .value = malloc(sizeof(int) * INCREMENT)};
    int shift;

    if (load_string(&input))
    {
        encrypt(&input);

        print_string(input);
    }

    return 0;
}