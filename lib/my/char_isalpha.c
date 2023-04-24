/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** char_isalpha.c
*/

#include "my.h"
#include <stdbool.h>

bool char_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    return false;
}
