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

void add_alias(char **env, char **cmd)
{
    int fd = get_alias_file_fd(env);

    if (fd == -1)
        return;
    write(fd, cmd[1], strlen(cmd[1]));
    write(fd, "\t", 1);
    for (int i = 2; i < my_arraylen(cmd); i++) {
        write(fd, " ", 1);
        write(fd, cmd[i], strlen(cmd[i]));
    }
    write(fd, "\n", 1);
    close(fd);
}
