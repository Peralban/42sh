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
#include <stdbool.h>

//Function to add variable with (or not) is value in env array
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
    if (tmp == NULL)
        return 1;
    tmp[0] = '\0';
    tmp = strcat(tmp, args[1]);
    tmp = strcat(tmp, "=");
    args[1] = strdup(tmp);
    if (args[2] == NULL)
        variable_only(env, args[1]);
    else
        variable_and_value(env, args);
    free(tmp);
    return 0;
}
