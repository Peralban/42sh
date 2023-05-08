/*
** EPITECH PROJECT, 2023
** execute_alias.c
** File description:
** functions that execute the needed aliases
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void execute_alias(char **cmd, char **env, int *error, int *exit_value)
{
    char *alias_cmd = get_cmd_from_alias(env, cmd[0]);
    char **alias_cmd_array = NULL;

    if (alias_cmd == NULL)
        return;
    alias_cmd_array = malloc(sizeof(char *) * (my_arraylen(cmd) + 1));
    alias_cmd_array[0] = strdup(alias_cmd);
    for (int i = 1; cmd[i] != NULL; i++)
        alias_cmd_array[i] = strdup(cmd[i]);
    alias_cmd_array[my_arraylen(cmd)] = NULL;
    exec_command(env, alias_cmd_array, error, exit_value);
    return;
}
