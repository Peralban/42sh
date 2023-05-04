/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** env_management.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

//Function to add variable with (or not) is value in env array
static void my_realloc_env(char **env, int array_size)
{
    char **new_env = malloc(sizeof(char *) * (array_size));
    int i = 0;

    while (env[i] != NULL) {
        new_env[i] = strdup(env[i]);
        i++;
    }
    new_env[i] = NULL;
    env = new_env;
    free(new_env);
}

static int variable_only(char **env, char **args)
{
    int array_size = my_arraylen(env);
    int i = 0;

    while (env[i] != NULL) {
        if (my_start_with(env[i], args[1]) == 1) {
            env[i] = malloc(sizeof(char) *
            strlen(args[1]) + 1);
            env[i] = strdup(args[1]);
            return 0;
        }
        i++;
    }
    my_realloc_env(env, array_size + 2);
    env[array_size] = malloc(sizeof(char) *
    strlen(args[1]) + 1);
    env[array_size] = strdup(args[1]);
    env[array_size + 1] = NULL;
    return 0;
}

static int variable_and_value(char **env, char **args)
{
    int array_size = my_arraylen(env);
    int i = 0;

    while (env[i] != NULL && array_size != 0) {
        if (my_start_with(env[i], args[1]) == 1) {
            env[i] = malloc(sizeof(char) *
            (strlen(args[1]) + strlen(args[2]) + 2));
            env[i] = strcat(args[1], args[2]);
            return 0;
        }
        i++;
    }
    my_realloc_env(env, array_size + 2);
    env[array_size] = malloc(sizeof(char) *
    (strlen(args[1]) + strlen(args[2]) + 2));
    env[array_size] = strcat(args[1], args[2]);
    env[array_size + 1] = NULL;
    return 0;
}

static int setenv_error(char **args, int *return_value, char **env)
{
    int nbr_args = my_arraylen(args);

    if (nbr_args > 3) {
        my_puterror("setenv: Too many arguments.\n");
        *return_value = 1;
        return 1;
    } else if (args[1] == NULL) {
        put_array_in_term(1, env);
        return 1;
    }
    if (parse_args_setenv(args) == 1) {
        *return_value = 1;
        return 1;
    }
    return 0;
}

int my_setenv(char **args, char **env, int *return_value)
{
    char *tmp = NULL;

    if (setenv_error(args, return_value, env) == 1)
        return 1;
    tmp = malloc(sizeof(char) * (strlen(args[1]) + 2));
    tmp = strcpy(tmp, args[1]);
    tmp = strcat(args[1], "=");
    args[1] = strdup(tmp);
    if (args[2] == NULL)
        variable_only(env, args);
    else
        variable_and_value(env, args);
    free(tmp);
    return 0;
}
