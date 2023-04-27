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

static void arr_remove(char ***arr_p, int i)
{
    char **arr = arr_p[0];
    int j = 0;

    arr[i] = NULL;
    for (j = i + 1; arr[j] != NULL; j++) {
        arr[j - 1] = arr[j];
    }
    arr[j - 1] = NULL;
}

static int arr_append(char ***arr_p, char *elem)
{
    char **arr = arr_p[0];
    char **tmp = NULL;
    int len = my_arraylen(arr);

    tmp = malloc(sizeof(char*) * (len + 2));
    if (tmp == NULL || elem == NULL)
        return 1;
    for (int i = 0; i < len; i++)
        tmp[i] = arr[i];
    tmp[len] = elem;
    tmp[len + 1] = NULL;
    arr_p[0] = tmp;
    return 0;
}

static bool isin(char c, char *delim)
{
    for (int i = 0; delim[i] != 0; i++) {
        if (c == delim[i])
            return true;
    }
    return false;
}

static static char *my_strdupij(char *str, int begin, int end)
{
    char *tmp = malloc(end - begin + 1);

    if (tmp == NULL)
        return NULL;
    for (int i = begin; i < end; i++)
        tmp[i - begin] = str[i];
    tmp[end - begin] = '\0';
    return tmp;
}

char **my_str_to_word_array(char *str, char *delim)
{
    int begin = 0;
    int end = 0;
    int i = 1;
    char **arr = malloc(sizeof(char*));
    if (str == NULL || arr == NULL)
        return NULL;
    arr[0] = NULL;
    for (; str[i] != 0; i++) {
        if (isin(str[i - 1], delim) && !(isin(str[i], delim)))
            begin = i;
        if (!(isin(str[i - 1], delim)) && isin(str[i], delim)) {
            end = i;
            arr_append(&arr, my_strdupij(str, begin, end));
        }
    } if (!(isin(str[i - 1], delim))) {
        end = i;
        if (arr_append(&arr, my_strdupij(str, begin, end)) == 1)
            return NULL;
    }
    return arr;
}
