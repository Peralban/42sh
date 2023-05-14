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

static int history_managemnt(char **cmd, int fd, int *error)
{
    if (strcmp(cmd[0], "history-clear") == 0 && my_arraylen(cmd) == 1) {
        fd = open(get_path(".42sh_history"), O_RDWR | O_CREAT | O_TRUNC, 0666);
        return history_error(fd, error);
    } else if (strcmp(cmd[0], "history") == 0 && my_arraylen(cmd) == 1) {
        write(fd, cmd[0], strlen(cmd[0]));
        write(fd, "\n", 1);
        close(fd);
        print_history();
        return 0;
    } else {
        return add_in_history(cmd, fd);
    }
}

static int search_cmd(char ***cmd)
{
    char **history = get_history_array();

    if (strlen(*cmd[0]) == 1)
        return 1;
    if (history == NULL)
        return 84;
    for (int i = my_arraylen(history) - 1; i >= 0; i--) {
        if (my_start_with(history[i], (*cmd[0]) + 1) == 1) {
            *cmd = my_str_to_word_array(history[i], " \t");
            return 1;
        }
    }
    return 1;
}

int history(char ***cmd, int *error)
{
    int fd = 0;

    fd = open(get_path(".42sh_history"), O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (history_error(fd, error) == 84)
        return 84;
    if (my_start_with(*cmd[0], "!") == 1)
        return search_cmd(cmd);
    return history_managemnt(*cmd, fd, error);
}
