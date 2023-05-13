/*
** EPITECH PROJECT, 2023
** echo.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *adapt_str(char *str)
{
    char *new_str = malloc(sizeof(char) * strlen(str));
    int j = 0;

    if (new_str == NULL)
        return NULL;
    for (int i = 1; str[i] != '\"' && str[i] != '\0'; i++) {
        if (str[i] == '\\')
            handle_backslash(str, new_str, i++, j);
        else
            new_str[j] = str[i];
        j++;
    }
    new_str[j] = '\0';
    return new_str;
}

char *test_echo_special_cases(char *str)
{
    if (str == NULL)
        return NULL;
    if (str[0] == '\"' || str[0] == '\'')
        return adapt_str(str);
    return str;
}

int my_echo(char **cmd, int *error)
{
    bool opt = false;
    char *str = NULL;

    if (cmd == NULL)
        return 0;
    opt = ((cmd[1] != NULL && strcmp(cmd[1], "-n") == 0) ? true : false);
    for (int i = (opt ? 2 : 1); cmd[i] != NULL; i++) {
        str = test_echo_special_cases(cmd[i]);
        my_putstr(str);
        if (cmd[i + 1] != NULL)
            my_putstr(" ");
    }
    if (!opt)
        my_putstr("\n");
    free(str);
    return *error;
}
