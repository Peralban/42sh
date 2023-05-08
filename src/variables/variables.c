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
#include <unistd.h>

char *find_num_variable(char *str, char **wa, int i, char **env)
{
    char *tmp = NULL;

    if (str[i + 1] == '0')
        return NULL;
    if (str[i + 1] <= '9' && str[i + 1] >= '0') {
        if (wa[str[i + 1] - '0'] == NULL)
            return NULL;
        if (wa[str[i + 1] - '0'][0] == '$')
            return my_getenv(env, (wa[str[i + 1] - '0'] + 1));
    }
    tmp = my_getenv(env, get_var(str, i + 1));
    if (tmp != NULL)
        return tmp;
    return find_local_variable(str, i);
}

char *create_new_line(char *new_line, char *tmp, int size)
{
    tmp = (tmp == NULL) ? " " : tmp;
    size = strlen(new_line) + strlen(tmp) + 2;
    new_line = realloc(new_line, sizeof(char) * size);
    new_line = strcat(new_line, tmp);
    new_line[size - 1] = '\0';
    return new_line;
}

char *detect_variables(char *line, char **env, int *error)
{
    int size = strlen(line) + 1;
    char *new_line = malloc(sizeof(char) * size);
    char *tmp = NULL;
    bool in_variable = detect_variable_attribution(&line);

    new_line[0] = '\0';
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '$') {
            tmp = find_special_variable(line, i, env, error);
            new_line = create_new_line(new_line, tmp, size);
            i++;
            in_variable = true;
            continue;
        }
        if (in_variable == false)
            new_line = strncat(new_line, &line[i], 1);
        in_variable = (in_variable == true && line[i] != ' ' ? true : false);
    }
    new_line[strlen(new_line)] = '\0';
    return new_line;
}
