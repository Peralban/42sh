/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** history.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

static int history_error(int fd, int *error)
{
    if (fd == -1) {
        *error = 1;
        return 84;
    }
    return 0;
}

static void print_history(void)
{
    char *line = NULL;
    FILE *fd = fopen(get_path(".42sh_history"), "r");
    size_t len = 0;
    int i = 1;

    if (fd == NULL)
        return;
    while (getline(&line, &len, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        my_putnbr(i);
        my_putstr("\t");
        my_putstr(line);
        my_putstr("\n");
        i++;
    }
    fclose(fd);
}

static int add_in_history(char *line, int fd)
{
    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    close(fd);
    return 0;
}

static int history_managemnt(char *line, int fd, int *error)
{
    if (strcmp(line, "history-clear") == 0) {
        fd = open(get_path(".42sh_history"), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (history_error(fd, error) == 84)
            return 84;
    } else if (strcmp(line, "history") == 0) {
        close(fd);
        print_history();
    } else {
        if (add_in_history(line, fd) == 84)
            return 84;
        return 0;
    }
    return 1;
}

static int search_cmd(char **line)
{
    char **history = get_history_array();

    if (strlen(*line) == 1)
        return 0;
    if (history == NULL)
        return 84;
    for (int i = my_arraylen(history) - 1; i >= 0; i--) {
        if (my_start_with(history[i], (*line) + 1) == 1) {
            (*line) = strdup(history[i]);
            return 0;
        }
    }
    return 0;
}

int history(char **line, int *error)
{
    int fd = 0;

    if (*line[0] == '\0')
        return 0;
    fd = open(get_path(".42sh_history"), O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (history_error(fd, error) == 84)
        return 84;
    if (my_start_with(*line, "!") == 1)
        return search_cmd(line);
    return history_managemnt(*line, fd, error);
}
