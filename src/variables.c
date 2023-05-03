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

int get_back_cmd(void)
{
    return -1;
}

char *find_local_variable(char *str, int i)
{
    (void)str;
    (void)i;
    return NULL;
}

char *join_all_args(char *str)
{
    char *tmp = malloc(sizeof(char *) * strlen(str) + 1);
    int j = 0;
    bool dont_print = true;

    if (str == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (dont_print && str[i] != ' ')
            continue;
        if (dont_print && str[i] == ' ') {
            dont_print = false;
            continue;
        }
        if (str[i] == '$') {
            dont_print = true;
            continue;
        }
        tmp[j] = str[i];
        j++;
    }
    tmp[j - 1] = '\0';
    return tmp;
}

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
    tmp = my_getenv(env, (str + i + 1));
    if (tmp != NULL)
        return my_getenv(env, (str + i + 1));
    return find_local_variable(str, i);
}

char *find_other_variable(char *str, char **wa, int i, char **env)
{
    int id = 0;

    switch (str[i + 1]) {
        case '!':
            id = get_back_cmd();
            if (id == -1)
                return NULL;
            else
                return NULL;
        case '-':
            return NULL;
        case '_':
            return NULL;
        default:
            return find_num_variable(str, wa, i, env);
    }
}

char *find_special_variable(char *str, int i, char **env, int *error)
{
    char *buff = malloc(sizeof(char) * 100);
    char **wa = my_str_to_word_array(str, " \t\n");

    switch (str[i + 1]) {
        case '$':
            sprintf(buff, "%d", getpid());
            return buff;
        case '#':
            sprintf(buff, "%d", my_arraylen(wa) - 1);
            return buff;
        case '*':
            return join_all_args(str);
        case '@':
            return NULL;
        case '?':
            sprintf(buff, "%d", *error);
            return buff;
        default:
            return find_other_variable(str, wa, i, env);
    }
}

char *create_new_line(char *new_line, char *tmp, int size)
{
    tmp = (tmp == NULL) ? " " : tmp;
    size = strlen(new_line) + strlen(tmp) + 2;
    new_line = realloc(new_line, sizeof(char) * size);
    new_line = strcat(new_line, tmp);
    new_line[size - 2] = ' ';
    new_line[size - 1] = '\0';
    return new_line;
}

char *detect_variables(char *line, char **env, int *error)
{
    int size = strlen(line) + 1;
    char *new_line = malloc(sizeof(char) * size);
    char *tmp = NULL;
    bool in_variable = false;

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
    new_line[strlen(new_line) - 1] = '\0';
    return new_line;
}
