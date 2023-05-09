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

char *adapt_str(char *str, int nb_quotes)
{
    char *new_str = malloc(sizeof(char) * strlen(str) - nb_quotes + 1);
    int j = 0;
    bool quote = false;

    if (new_str == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        quote = ((str[i] == '\"' || str[i] == '\'') ? !quote : quote);
        if (str[i] == '\\' && quote) {
            handle_backslash(str, new_str, i++, j++);
            continue;
        }
        if (str[i] == '\"' || str[i] == '\'' || str[i] == '\\')
            continue;
        new_str[j] = str[i];
        j++;
    }
    new_str[j] = '\0';
    return new_str;
}

char *test_echo_special_cases(char *str)
{
    int nb_db_quotes = 0;
    int nb_quotes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            nb_db_quotes++;
        if (str[i] == '\'')
            nb_quotes++;
    }
    if (nb_db_quotes % 2 != 0)
        return strdup("Unmatched '\"'.");
    if (nb_quotes % 2 != 0)
        return strdup("Unmatched '\''.");
    return adapt_str(str, nb_quotes + nb_db_quotes);
}

int my_echo(char *line, int *error)
{
    char **cmd = my_str_to_word_array(line, " \t");
    bool opt = ((cmd[0] != NULL && strcmp(cmd[0], "-n") == 0) ? true : false);
    char *str = NULL;

    if (cmd == NULL)
        return 0;
    if (opt)
        line = line + 2;
    str = test_echo_special_cases(line);
    if (str == NULL)
        return 0;
    my_putstr(str);
    if (!opt)
        my_putstr("\n");
    free(str);
    return *error;
}

bool echo_execution(char *line, int *error)
{
    if (line == NULL)
        return false;
    if (strcmp(line, "echo") == 0) {
        my_putstr(" \n");
        return true;
    }
    if (strncmp(line, "echo ", 5) != 0)
        return false;
    *error = my_echo((line + 5), error);
    return true;
}
