/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** str_isalpahnum.c
*/

#include "my.h"
#include <stdbool.h>

bool str_isalphanum(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (char_isnum(str[i]) == false && char_isalpha(str[i]) == false)
            return false;
        i++;
    }
    return true;
}
