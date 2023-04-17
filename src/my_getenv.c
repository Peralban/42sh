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
char *my_getenv(char **env, char *str)
{
    int v_size = strlen(str);
    char *v_path = 0;

    for (int index = 0; env[index] != NULL; index++) {
        if (my_start_with(env[index], str) && env[index][v_size] == '=') {
            v_path = strdup(env[index] + v_size + 1);
            return v_path;
        }
    }
    return NULL;
}
