/*
** EPITECH PROJECT, 2023
** variable_builtins.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <stdio.h>

void delete_local_variable(char *name)
{
    char *path = get_path(".42sh_variables");
    char *tmp = get_path(".42sh_variables_tmp");
    char *line = NULL;
    FILE *fd = fopen(path, "r");
    FILE *fd_tmp = fopen(tmp, "w");
    size_t len = 0;

    if (fd == NULL || fd_tmp == NULL)
        return;
    while (getline(&line, &len, fd) != -1)
        if (strncmp(line, name, strlen(name)) != 0)
            fprintf(fd_tmp, "%s", line);
    fclose(fd);
    fclose(fd_tmp);
    remove(path);
    rename(tmp, path);
    free(path);
    free(tmp);
    free(line);
}

void append_local_variable(char *name, char *value)
{
    char *path = get_path(".42sh_variables");
    FILE *fd = NONE;

    delete_local_variable(name);
    fd = fopen(path, "a");
    fprintf(fd, "%s %s\n", name, value);
    fclose(fd);
    free(path);
}

int display_local_variables(void)
{
    char *path = get_path(".42sh_variables");
    FILE *fd = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;

    if (fd == NULL)
        return 1;
    while (getline(&line, &len, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        my_putstr(line);
        my_putstr("\n");
    }
    fclose(fd);
    free(path);
    free(line);
    return 0;
}

int my_set(char **cmd, int *error)
{
    char *name = NULL;
    char *value = NULL;

    if (cmd[1] == NULL) {
        *error = display_local_variables();
        return *error;
    }
    for (int i = 1; cmd[i] != NULL; i++) {
        name = get_var_name(cmd[i], 0);
        value = get_var_value(cmd[i], 0);
        append_local_variable(name, value);
    }
    free(name);
    free(value);
    return 0;
}

int my_unset(char **cmd, int *error)
{
    char *name = NULL;

    if (cmd[1] == NULL) {
        my_putstr("unset: Too few arguments.\n");
        *error = 1;
        return *error;
    }
    for (int i = 1; cmd[i] != NULL; i++) {
        name = cmd[i];
        delete_local_variable(name);
    }
    free(name);
    return 0;
}
