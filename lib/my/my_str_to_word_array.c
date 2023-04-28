/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_str_to_word_array.c
*/

#include "my.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *my_strdupij(char *str, int begin, int end)
{
    char *new_str = malloc(sizeof(char) * (end - begin + 1));
    int i = 0;

    for (; begin < end; begin++) {
        new_str[i] = str[begin];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}

bool isin(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++)
        if (c == delim[i])
            return true;
    return false;
}

int count_words(char *str, char *delim)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (!isin(str[i], delim) && (isin(str[i + 1], delim) ||
        str[i + 1] == '\0'))
            count++;
    return count;
}

void find_end(char *str, char *delim, int *i)
{
    for (; !isin(str[*i], delim) && str[*i] != '\0'; (*i)++);
}

char **my_str_to_word_array(char *str, char *delim)
{
    int words = count_words(str, delim);
    char **array = malloc(sizeof(char *) * (words + 1));
    int i = 0;
    int j = 0;
    int k = 0;

    for (; str[i] != '\0'; i++) {
        if (!isin(str[i], delim)) {
            j = i;
            find_end(str, delim, &i);
            array[k] = my_strdupij(str, j, i);
            k++;
        }
    }
    array[k] = NULL;
    return array;
}
