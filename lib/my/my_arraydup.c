/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_arraydup.c
*/

#include "my.h"
#include <string.h>
#include <stdlib.h>

char **my_arraydup(char **src)
{
    char **dest = malloc(sizeof(char *) * (my_arraylen(src) + 1));
    int i = 0;

    if (src == NULL)
        return NULL;
    while (src[i] != NULL) {
        dest[i] = strdup(src[i]);
        i++;
    }
    dest[i] = NULL;
    return dest;
}
