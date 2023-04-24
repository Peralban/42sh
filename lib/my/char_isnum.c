/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** char_isnum.c
*/

#include "my.h"
#include <stdbool.h>

bool char_isnum(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
