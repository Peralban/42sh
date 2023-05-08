/*
** EPITECH PROJECT, 2023
** command_error_handling.c
** File description:
** Handle all the commands error
*/

#include "mysh.h"
#include "command_error_handling.h"
#include "my.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int check_access(char *cmd, bool *not_access)
{
    if (access(cmd, F_OK) == 0) {
        if (access(cmd, X_OK) != 0) {
            *not_access = true;
            return NOT_ACCESSIBLE;
        }
        return ACCESSIBLE;
    }
    return NOT_EXISTING;
}

static char *get_tmp(char *path, char *cmd)
{
    char *tmp = malloc(sizeof(char) * (strlen(path) + strlen(cmd) + 2));

    if (tmp == NULL)
        return NULL;
    tmp[0] = '\0';
    tmp = strcat(tmp, path);
    tmp = strcat(tmp, "/");
    tmp = strcat(tmp, cmd);
    tmp[strlen(path) + strlen(cmd) + 1] = '\0';
    return tmp;
}

static char *exist_in_path(char *cmd, char *path, int *error)
{
    char *tmp = NULL;
    char **path_tab = my_str_to_word_array(path, ":");
    bool not_access = false;

    if (path_tab == NULL) {
        *error = 1;
        return NULL;
    }
    for (int i = 0; path_tab[i] != NULL; i++) {
        tmp = get_tmp(path_tab[i], cmd);
        if (check_access(tmp, &not_access) == ACCESSIBLE) {
            destroy_array(path_tab);
            return tmp;
        }
        free(tmp);
    }
    destroy_array(path_tab);
    if (not_access == true)
        my_put_permission_denied(cmd);
    return NULL;
}

char *search_command(char *cmd, char **env, int *error)
{
    char *path = my_getenv(env, "PATH");
    char *tmp = NULL;

    if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
        return cmd;
    if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
        return cmd;
    if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0) {
        my_put_permission_denied(cmd);
        return NULL;
    }
    tmp = exist_in_path(cmd, path, error);
    if (tmp != NULL) {
        free(path);
        return tmp;
    } else {
        free(path);
        my_put_command_not_found(cmd);
        return NULL;
    }
}
