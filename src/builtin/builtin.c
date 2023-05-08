/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** built-in.c
*/

#include "mysh.h"
#include "my.h"
#include <string.h>

int built_in(char **cmd, char **env, int *error, int *exit_value)
{
    *error = 0;
    if (strcmp(cmd[0], "cd") == 0)
        return my_cd(cmd, env, error);
    if (strcmp(cmd[0], "env") == 0) {
        print_array(env);
        return 0;
    }
    if (strcmp(cmd[0], "setenv") == 0)
        return my_setenv(cmd, env, error);
    if (strcmp(cmd[0], "unsetenv") == 0)
        return my_unsetenv(cmd, env, error);
    if (strcmp(cmd[0], "exit") == 0)
        return my_exit(exit_value);
    if (strcmp(cmd[0], "echo") == 0)
        return my_echo(cmd, error);
    return 2;
}
