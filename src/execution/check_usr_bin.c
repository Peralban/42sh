/*
** EPITECH PROJECT, 2023
** check_usr_bin.c
** File description:
** check if the function is in /usr/bin
*/

#include "mysh.h"
#include "command_error_handling.h"
#include <string.h>

char *check_usr_bin(char *cmd, int *error)
{
    char *path = strdup("/usr/bin/");
    char *tmp = get_tmp(path, cmd);
    bool not_access = false;

    if (check_access(tmp, &not_access) == ACCESSIBLE) {
        free(path);
        return tmp;
    }
    free(path);
    free(tmp);
    *error = 1;
    return NULL;
}
