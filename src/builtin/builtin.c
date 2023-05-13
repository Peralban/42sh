/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** built-in.c
*/

#include "mysh.h"
#include "my.h"
#include <string.h>

char **delete_quotes(char **cmd)
{
    for (int i = 0; cmd[i] != NULL; i++)
        if (cmd[i][0] == '\"' || cmd[i][0] == '\'') {
            cmd[i] = cmd[i] + 1;
            cmd[i][strlen(cmd[i]) - 1] = '\0';
        }
    return cmd;
}

int local_var_built_in(char **cmd, int *error)
{
    if (strcmp(cmd[0], "set") == 0)
        return my_set(cmd, error);
    if (strcmp(cmd[0], "unset") == 0)
        return my_unset(cmd, error);
    return 2;
}

int built_in(char **cmd, char **env, int *error, int *exit_value)
{
    *error = 0;
    if (strcmp(cmd[0], "echo") == 0)
        return my_echo(cmd, error);
    cmd = delete_quotes(cmd);
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
    return local_var_built_in(cmd, error);
}
