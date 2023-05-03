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
        my_puterror("open");
        *error = 1;
        return 84;
    }
    return 0;
}

static void print_history(void)
{
    char *line = NULL;
    FILE *fd = fopen(".42sh_history", "r");
    size_t len = 0;
    int i = 1;

    while (getline(&line, &len, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        my_putnbr(i);
        my_putstr("\t");
        my_putstr(line);
        my_putstr("\n");
        i++;
    }
}

static int add_in_history(char *line, int fd, int *error)
{
    char *str = malloc(sizeof(char) * (strlen(line) + 2));

    if (str == NULL) {
        *error = 1;
        return 84;
    }
    str = strcat(line, "\n");
    write(fd, str, strlen(str));
    return 0;
}

int history(char *line, int *error)
{
    int fd = 0;

    if (line[0] == '\0')
        return 0;
    fd = open(".42sh_history", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (history_error(fd, error) == 84)
        return 84;
    if (strcmp(line, "history-clear") == 0) {
        fd = open(".42sh_history", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (history_error(fd, error) == 84)
            return 84;
    } else if (strcmp(line, "history") == 0) {
        close(fd);
        print_history();
        return 0;
    } else {
        if (add_in_history(line, fd, error) == 84)
            return 84;
    }
    return 0;
}
