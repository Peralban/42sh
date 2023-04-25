/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** var_are_init.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

// This function return true if the variable [home], [pwd], [oldpwd] and [user]
// are initialized.
static void loop_var_init(char **env, int *var_init, int index, char *var[])
{
    for (int i = 0; i < 4; i++) {
        if (my_start_with(env[index], var[i]))
            *var_init += 1;
    }
}

bool var_are_init(char **env)
{
    int env_size = my_arraylen(env);
    int var_init = 0;
    char *var[] = {"HOME", "PWD", "OLDPWD", "USER"};

    for (int index = 0; index < env_size; index++) {
        loop_var_init(env, &var_init, index, var);
    }
    if (var_init == 4)
        return true;
    return false;
}
