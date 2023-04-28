/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** built-in.c
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int built_in(char **cmd, char **env, int *error)
{
    (void) *error;
    if (strcmp(cmd[0], "cd") == 0)
        return 1;
    if (strcmp(cmd[0], "env") == 0) {
        put_array_in_term(1, env);
        return 0;
    }
    if (strcmp(cmd[0], "setenv") == 0)
        return my_setenv(cmd, env);
    if (strcmp(cmd[0], "unsetenv") == 0)
        return my_unsetenv(cmd, env);
    if (strcmp(cmd[0], "exit") == 0)
        return 1;
    return 2;
}
