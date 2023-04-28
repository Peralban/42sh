/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_unsetenv.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

//Function to delete one or many variable(s) in env array
static int delete_var(char **args, char **env, int i)
{
    for (int index = 0; env[index] != NULL; index++) {
        if (my_start_with(env[index], args[i]) == 1) {
            delete_str_in_array(env, index);
            break;
        }
    }
    return 0;
}

int my_unsetenv(char **args, char **env, int *return_value)
{
    int nbr_args = my_arraylen(args);
    char *tmp = NULL;

    if (nbr_args < 2) {
        my_puterror("unsetenv: Too few arguments.\n");
        *return_value = 1;
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++) {
        tmp = malloc(sizeof(char) * (strlen(args[i]) + 2));
        tmp = strcat(args[i], "=");
        args[i] = strdup(tmp);
        delete_var(args, env, i);
    }
    free(tmp);
    return 0;
}
