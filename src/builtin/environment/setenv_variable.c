/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set_variable_and_value.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool variable_exist(char **env, char *variable)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_start_with(env[i], variable) == true)
            return true;
    }
    return false;
}

static void reset_variable(char **env, char *var, char *value)
{
    char *tmp = malloc(sizeof(char) * (strlen(var) + 1));

    if (tmp == NULL)
        return;
    tmp[0] = '\0';
    strcat(tmp, var);
    if (value != NULL) {
        tmp = realloc(tmp, sizeof(char) * (strlen(var) + strlen(value) + 1));
        if (tmp == NULL)
            return;
        strcat(tmp, value);
    }
    for (int i = 0; env[i] != NULL; i++)
        if (my_start_with(env[i], var) == true) {
            free(env[i]);
            env[i] = strdup(tmp);
            free(tmp);
            return;
        }
}

static int complete_new_env(char **new_env, char **args, int i)
{
    char *tmp = NULL;

    tmp = malloc(sizeof(char) * (strlen(args[1]) + strlen(args[2]) + 1));
    if (tmp == NULL)
        return 1;
    tmp[0] = '\0';
    tmp = strcat(tmp, args[1]);
    tmp = strcat(tmp, args[2]);
    new_env[i] = strdup(tmp);
    new_env[i + 1] = NULL;
    free(tmp);
    return 0;
}

void variable_and_value(char **env, char **args)
{
    int i = 0;
    char **new_env = NULL;

    if (variable_exist(env, args[1]) == true) {
        reset_variable(env, args[1], args[2]);
        return;
    }
    new_env = malloc(sizeof(char *) * (my_arraylen(env) + 2));
    if (new_env == NULL)
        return;
    for (; i < my_arraylen(env); i++)
        new_env[i] = env[i];
    if (complete_new_env(new_env, args, i) == 0) {
        set_env_tab(new_env);
    } else {
        for (int j = 0; new_env[j] != NULL; j++)
            free(new_env[j]);
        free(new_env);
    }
}

void variable_only(char **env, char *variable)
{
    int i = 0;
    char **new_env = NULL;

    if (variable_exist(env, variable) == true) {
        reset_variable(env, variable, NULL);
        return;
    }
    new_env = malloc(sizeof(char *) * (my_arraylen(env) + 2));
    if (new_env == NULL)
        return;
    for (; i < my_arraylen(env); i++)
        new_env[i] = env[i];
    new_env[i] = strdup(variable);
    new_env[i + 1] = NULL;
    set_env_tab(new_env);
}
