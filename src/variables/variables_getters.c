/*
** EPITECH PROJECT, 2022
** variables_getters.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <stdio.h>

char *get_var(char *str, int i)
{
    char *tmp = malloc(sizeof(char *) * strlen(str) + 1);
    int j = 0;

    if (str == NULL || tmp == NULL)
        return NULL;
    while (str[i] != '\0' && str[i] != ' ') {
        tmp[j] = str[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return tmp;
}

char *get_var_name(char *str, int i)
{
    char *tmp = malloc(sizeof(char *) * strlen(str) + 1);
    int j = 0;

    if (str == NULL || tmp == NULL)
        return NULL;
    while (str[i] != '\0' && str[i] != ' ')
        i--;
    i++;
    while (str[i] != '=') {
        tmp[j] = str[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return tmp;
}
