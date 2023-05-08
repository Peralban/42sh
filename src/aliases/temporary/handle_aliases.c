/*
** EPITECH PROJECT, 2023
** handle_aliases.c
** File description:
** contains functions to handle the different features of the alias command
*/

#include "mysh.h"
#include "my.h"
#include <string.h>

static void print_aliases(char **env)
{
    char **aliases = get_alias_file(env);

    if (aliases == NULL)
        return;
    for (int i = 0; aliases[i] != NULL; i++) {
        my_putstr(aliases[i]);
        my_putstr("\n");
    }
    destroy_array(aliases);
}

void handle_aliases(char **cmd, char **env, int *error, int *exit_value)
{
    if (cmd == NULL || cmd[0] == NULL)
        return;
    if (my_arraylen(cmd) == 1 && strcmp(cmd[0], "alias") == 0) {
        print_aliases(env);
        return;
    }
    if (strcmp(cmd[1], "alias") == 0) {
        add_alias(env, cmd);
        return;
    }
    if (strcmp(cmd[1], "unalias") == 0) {
        remove_alias(env, cmd);
        return;
    }
    execute_alias(cmd, env, error, exit_value);
}
