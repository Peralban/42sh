/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_getenv.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

// This function return the value of the environment variable [str] in [env].
// If it doesn't exists it returns NULL.
char *my_getenv(char **env, char *var)
{
    int var_size = strlen(var);
    char *var_path = 0;

    if (env == NULL || var == NULL)
        return NULL;
    for (int index = 0; env[index] != NULL; index++) {
        if (my_start_with(env[index], var) && env[index][var_size] == '=') {
            var_path = strdup(env[index] + var_size + 1);
            return var_path;
        }
    }
    return NULL;
}
