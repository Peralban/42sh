/*
** EPITECH PROJECT, 2023
** variables_special_cases.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <stdio.h>
#include <string.h>

int get_back_cmd(void)
{
    return -1;
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
        if ((dont_print && str[i] == ' ') || str[i] == '$') {
            dont_print = !dont_print;
            continue;
        }
        tmp[j] = str[i];
        j++;
    }
    tmp[j - 1] = '\0';
    return tmp;
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
