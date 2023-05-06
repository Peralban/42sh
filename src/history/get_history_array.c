/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** get_histry_array.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

static int put_line_edition_error(char *str)
{
    my_puterror(str);
    return -1;
}

static int open_history_file(void)
{
    char *history_path = get_history_path();
    int fd = 0;

    if (history_path == NULL)
        return -1;
    fd = open(history_path, O_CREAT | O_RDONLY | O_APPEND, 0664);
    if (fd == -1)
        return put_line_edition_error("open");
    return fd;
}

static char *read_history_file(int fd)
{
    struct stat st;
    char *history_path = get_history_path();
    char *history_in_line = NULL;

    stat(history_path, &st);
    history_in_line = malloc(sizeof(char) * (st.st_size + 1));
    if (read(fd, history_in_line, st.st_size) == -1) {
        put_line_edition_error("read");
        return NULL;
    }
    close(fd);
    history_in_line[st.st_size] = '\0';
    return history_in_line;
}

char **get_history_array(void)
{
    char **history = NULL;
    int fd = open_history_file();
    char *history_in_line = NULL;

    if (fd == -1)
        return NULL;
    history_in_line = read_history_file(fd);
    if (history_in_line == NULL)
        return NULL;
    history = my_str_to_word_array(history_in_line, "\n");
    if (history == NULL)
        return NULL;
    free(history_in_line);
    return history;
}
