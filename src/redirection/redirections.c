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

int get_term_fd(void)
{
    int fd = 0;
    char *term_name = get_term_name();

    if (term_name == NULL)
        return -1;
    fd = open(term_name, O_RDWR);
    if (fd == -1)
        return -1;
    return fd;
}

static void open_redirection(int *fd, special_type_e type, char *file_path)
{
    if (type == REDIR_RIGHT)
        *fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (type == DOUBLE_REDIR_RIGHT)
        *fd = open(file_path, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (type == REDIR_LEFT)
        *fd = open(file_path, O_RDONLY, 0644);
}

int redirect_left(int fd, special_type_e type, char *file_path)
{
    if (fd == -1) {
        my_puterror(file_path);
        my_puterror(": No such file or directory.\n");
        return 1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}

int redirect_right(int fd, special_type_e type, int fd_ncurse)
{
    if (fd == -1) {
        my_puterror("Failed to open file.\n");
        return 1;
    }
    dup2(fd, fd_ncurse);
    close(fd);
    return 0;
}

int redirection(char *file_path, special_type_e type)
{
    struct stat path;
    int fd = 0;
    int fd_ncurse = STDOUT_FILENO;

    if (stat(file_path, &path) == 0 && type == 3) {
        my_puterror(file_path);
        my_puterror(": Is a directory.\n");
        return 1;
    }
    open_redirection(&fd, type, file_path);
    if (is_ncurses() == true)
        fd_ncurse = get_term_fd();
    if (type == REDIR_LEFT)
        return redirect_left(fd, type, file_path);
    if (type == REDIR_RIGHT || type == DOUBLE_REDIR_RIGHT)
        return redirect_right(fd, type, fd_ncurse);
    return 0;
}