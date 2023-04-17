/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** built-in.c
*/

#include "mysh.h"
#include <string.h>

int built_in(char **cmd, char **env, int *error)
{
    (void) env;
    if (strcmp(cmd[0], "cd") == 0) {
        // my_cd(cmd, env);
        return 1;
    }
    if (strcmp(cmd[0], "env") == 0) {
        // my_env(*env);
        return 1;
    }
    if (strcmp(cmd[0], "setenv") == 0) {
        // my_setenv(cmd, env);
        return 1;
    }
    if (strcmp(cmd[0], "unsetenv") == 0) {
        // my_unsetenv(cmd, env);
        return 1;
    }
    if (strcmp(cmd[0], "exit") == 0) {
        my_exit(cmd, error);
        return 1;
    }
    return 0;
}