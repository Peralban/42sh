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

void delete_local_variable(char *name)
{
    char *path = get_path(".42sh_variables");
    FILE *fd = fopen(path, "a");
    char *line = NULL;
    size_t len = 0;

    if (fd == NULL)
        return;
    while (getline(&line, &len, fd) != -1) {
        if (strncmp(line, name, strlen(name)) == 0) {
            continue;
        }
        fprintf(fd, "%s", line);
    }
    fclose(fd);
}

void append_local_variable(char *name, char *value)
{
    char *path = get_path(".42sh_variables");
    FILE *fd = fopen(path, "a");

    if (fd == NULL)
        return;
    if (find_local_variable(name, 0) != NULL)
        delete_local_variable(name);
    fprintf(fd, "%s=%s\n", name, value);
    fclose(fd);
}

int handle_equal_sign(char **line, int i)
{
    char *name = NULL;
    char *value = NULL;

    name = get_var_name((*line), i);
    value = get_var((*line), i + 1);
    append_local_variable(name, value);
    return strlen(name);
}

bool detect_variable_attribution(char **line)
{
    bool in_variable = false;
    char *new_line = malloc(sizeof(char) * strlen(*line));
    int size = 0;

    if (new_line == NULL)
        return true;
    for (int i = 0; (*line)[i] != '\0'; i++) {
        if ((*line)[i] == '=') {
            size -= handle_equal_sign(line, i);
            in_variable = true;
            new_line[size++] = '\0';
        }
        if (in_variable == true && (*line)[i] == ' ')
            in_variable = false;
        if (in_variable == false)
            new_line[size++] = (*line)[i];
    }
    new_line[size] = '\0';
    *line = strcpy(*line, new_line);
    return false;
}

char *find_local_variable(char *str, int i)
{
    char *var = get_var(str, i + 1);
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
            fclose(fd);
            return tmp;
        }
    }
    fclose(fd);
    return NULL;
}
