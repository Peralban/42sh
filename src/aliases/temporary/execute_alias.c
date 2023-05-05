/*
** EPITECH PROJECT, 2023
** execute_alias.c
** File description:
** functions that execute the needed aliases
*/

#include "mysh.h"

void execute_alias(char **cmd, char **env, int *error)
{
    int fd = get_alias_file_fd(env);

    if (fd == -1)
        return;
    return;
}
