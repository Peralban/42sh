/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** right_redirection.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "parser.h"
#include <errno.h>

static void open_redirection(int *fd, special_type_e type, char *file_path)
{
    if (type == REDIR_RIGHT)
        *fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (type == DOUBLE_REDIR_RIGHT)
        *fd = open(file_path, O_CREAT | O_APPEND | O_WRONLY, 0644);
}

int right_redirection(char *file_path, special_type_e type)
{
    struct stat path;
    int fd = 0;

    if (stat(file_path, &path) == 0 && type == 3) {
        my_puterror(file_path);
        my_puterror(": Is a directory.\n");
        return 1;
    }
    open_redirection(&fd, type, file_path);
    if (fd == -1) {
        my_puterror(file_path);
        my_puterror(": ");
        my_puterror(strerror(errno));
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}
