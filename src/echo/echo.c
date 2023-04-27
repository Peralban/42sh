/*
** EPITECH PROJECT, 2023
** echo.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *adapt_str(char *str, int nb_quotes)
{
    int size = strlen(str) - nb_quotes;
    char *new_str = malloc(sizeof(char) * size + 1);
    int j = 0;

    if (new_str == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            continue;
        if (str[i] == '\\' && str[i + 1] != '\0' && str[i + 1] != 34) {
            handle_backslash(str, new_str, i, j);
            i++;
            j++;
            continue;
        }
        new_str[j] = str[i];
        j++;
    }
    new_str[j] = '\0';
    return new_str;
}

char *test_special_cases(char *str)
{
    int nb_quotes = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '"')
            nb_quotes++;
    if (nb_quotes % 2 != 0)
        return "Unmatched '\"'.";
    if (nb_quotes == 0)
        return str;
    return adapt_str(str, nb_quotes);
}

char *tab_to_str(char **cmd)
{
    char *str = NULL;
    int size = 0;

    for (int i = 1; cmd[i] != NULL; i++)
        size += strlen(cmd[i]) + 1;
    str = malloc(sizeof(char) * size + 1);
    if (str == NULL)
        return NULL;
    for (int i = 1; cmd[i] != NULL; i++) {
        strcat(str, cmd[i]);
        if (cmd[i + 1] != NULL)
            strcat(str, " ");
    }
    return str;
}

int my_echo(char **cmd, int *error)
{
    bool opt = ((cmd[1] != NULL && strcmp(cmd[1], "-n") == 0) ? true : false);
    char *str_cmd = tab_to_str(cmd);
    char *str = NULL;
    (void)error;

    str = test_special_cases(str_cmd);
    printf("%s", str);
    if (!opt)
        printf("\n");
    return 0;
}
