/*
** EPITECH PROJECT, 2023
** handle_aliases.c
** File description:
** contains functions to handle the different features of the alias command
*/

#include "mysh.h"
#include "my.h"
#include <string.h>

static void print_aliases(void)
{
    char **aliases = get_alias_file();

    if (aliases == NULL)
        return;
    for (int i = 0; aliases[i] != NULL; i++) {
        my_putstr(aliases[i]);
        my_putstr("\n");
    }
    destroy_array(aliases);
}

int handle_alias(char *line, int *error)
{
    if (strcmp(line, "alias") == 0) {
        print_aliases();
        *error = 0;
        return 1;
    }
    if (strncmp(line, "alias", 5) == 0) {
        add_alias(line, error);
        return 1;
    }
    if (strncmp(line, "unalias", 7) == 0) {
        remove_alias(line, error);
        return 1;
    }
    if (is_an_alias(line) == true) {
        execute_alias(line, error);
        return 1;
    }
    return 0;
}
