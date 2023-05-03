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

    if (new_str == NULL)
        return NULL;
    for (; begin < end; begin++) {
        new_str[i] = str[begin];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}

bool isin(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i])
            return true;
    }
    return false;
}

void arr_append(char ***arr_p, char *elem)
{
    char **arr = arr_p[0];
    char **tmp = NULL;
    int len = 0;

    for (; arr[len] != NULL; len++);
    tmp = malloc(sizeof(char *) * (len + 2));
    if (tmp == NULL)
        return;
    for (int i = 0; i < len; i++)
        tmp[i] = arr[i];
    tmp[len] = elem;
    tmp[len + 1] = NULL;
    arr_p[0] = tmp;
}

char **my_str_to_word_array(char *str, char *delim)
{
    int begin = 0;
    int end = 0;
    int i = 1;
    char **arr = malloc(sizeof(char *));

    if (str == NULL)
        return NULL;
    for (arr[0] = NULL; str[i] != '\0'; i++) {
        if (isin(str[i - 1], delim) && !(isin(str[i], delim)))
            begin = i;
        if (isin(str[i], delim) && !(isin(str[i - 1], delim))) {
            end = i;
            arr_append(&arr, my_strdupij(str, begin, end));
        }
    }
    if (isin(str[i - 1], delim))
        arr_append(&arr, my_strdupij(str, begin, i - 1));
    else
        arr_append(&arr, my_strdupij(str, begin, i));
    return arr;
}