/*
** EPITECH PROJECT, 2023
** local_variables.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <stdio.h>

void free_find_local_var(char *var, char *path, char *line, FILE *fd)
{
    free(var);
    free(path);
    free(line);
    fclose(fd);
}

char *find_local_variable(char *str, int i)
{
    char *var = get_var_name(str, i + 1);
    char *path = get_path(".42sh_variables");
    char *tmp = NULL;
    char *line = NULL;
    FILE *fd = fopen(path, "r");
    size_t len = 0;

    if (fd == NULL || var == NULL)
        return NULL;
    while (getline(&line, &len, fd) != -1) {
        if (strncmp(line, var, strlen(var)) == 0) {
            tmp = strdup(line + strlen(var) + 1);
            tmp[strlen(tmp) - 1] = '\0';
            free_find_local_var(var, path, line, fd);
            return tmp;
        }
    }
    free_find_local_var(var, path, line, fd);
    free(tmp);
    return NULL;
}
