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

char *handle_backslash(char *str, char *new_str, int i, int j)
{
    char *tmp = NULL;

    tmp = find_special_char(str[i + 1]);
        if (strlen(tmp) == 2) {
            new_str[j] = tmp[0];
            new_str[j + 1] = tmp[1];
            j++;
        } else
            new_str[j] = tmp[0];
    i++;
    j++;
    return new_str;
}

char *adapt_str(char *str, int nb_quotes)
{
    int size = strlen(str) - nb_quotes;
    char *new_str = malloc(sizeof(char) * size + 1);
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            continue;
        if (str[i] == '\\' && str[i + 1] != '\0' && str[i + 1] != 34) {
            handle_backslash(str, new_str, i, j);
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

int my_echo(char **cmd, int *error)
{
    bool opt = ((cmd[1] != NULL && strcmp(cmd[1], "-n") == 0) ? true : false);
    char *str = NULL;
    (void)error;

    for (int i = 1 + opt; cmd[i] != NULL; i++) {
        str = test_special_cases(cmd[i]);
        printf("%s", str);
        if (cmd[i + 1] != NULL)
            printf(" ");
    }
    if (!opt)
        printf("\n");
    return 0;
}
