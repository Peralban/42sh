/*
** EPITECH PROJECT, 2023
** add_alias.c
** File description:
** Functions to add an alias to the temporary file
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <string.h>

// void del_alias(char **env, char *alias)
// {

// }

void add_alias(char **env, char **cmd)
{
    int fd = get_alias_file_fd(env);
    int len = 0;

    if (fd == -1)
        return;
    len = my_arraylen(cmd);
    write(fd, cmd[1], strlen(cmd[1]));
    if (len == 2) {
        write(fd, " ", 1);
        write(fd, "\n", 1);
        close(fd);
        return;
    }
    for (int i = 2; i < len; i++) {
        write(fd, " ", 1);
        write(fd, cmd[i], strlen(cmd[i]));
    }
    write(fd, "\n", 1);
    close(fd);
}
