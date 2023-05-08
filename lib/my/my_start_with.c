/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_start_with.c
*/

#include "my.h"
#include <stdbool.h>

bool my_start_with(char *src, char *cmp)
{
    int i = 0;

    while (cmp[i] != '\0') {
        if (cmp[i] != src[i])
            return false;
        i++;
    }
    return true;
}
