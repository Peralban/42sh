/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_arraylen.c
*/

#include <stdlib.h>

int my_arraylen(char **array)
{
    int i = 0;

    if (array == NULL)
        return 0;
    while (array[i] != NULL)
        i++;
    return i;
}
