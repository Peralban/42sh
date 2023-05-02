/*
** EPITECH PROJECT, 2023
** variables.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *find_local_variable(char *str)
{
    (void)str;
    return NULL;
}

char *find_other_variable(char *str, char **env)
{
    char *tmp = NULL;

    if (str[1] == '0')
        return NULL;
    if (str[1] <= '9' && str[1] >= '0')
        return NULL;
    tmp = my_getenv(env, str + 1);
    if (tmp != NULL)
        return my_getenv(env, str + 1);
    return find_local_variable(str);
}

char *find_special_variable(char *str, char **env, int *error)
{
    char *buff = malloc(sizeof(char) * 100);

    switch (str[1]) {
        case '$':
            return NULL;
        case '#':
            return NULL;
        case '*':
            return NULL;
        case '@':
            return NULL;
        case '?':
            sprintf(buff, "%d", *error);
            return buff;
        case '!':
            return NULL;
        case '-':
            return NULL;
        case '_':
            return NULL;
        default:
            return find_other_variable(str, env);
    }
}

char **detect_variables(char **wa, char **env, int *error)
{
    char **new_wa = malloc(sizeof(char *) * (my_arraylen(wa) + 1));
    char *tmp = NULL;

    for (int i = 0; wa[i] != NULL; i++) {
        if (wa[i][0] == '$') {
            tmp = find_special_variable(wa[i], env, error);
            new_wa[i] = malloc(sizeof(char) * (strlen(tmp) + 1));
            strcpy(new_wa[i], tmp);
            continue;
        }
        new_wa[i] = malloc(sizeof(char) * (strlen(wa[i]) + 1));
        strcpy(new_wa[i], wa[i]);
    }
    return new_wa;
}
