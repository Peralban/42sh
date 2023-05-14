/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** add_in_history.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int add_in_history(char **cmd, int fd)
{
    for (int i = 0; cmd[i] != NULL; i++) {
        write(fd, cmd[i], strlen(cmd[i]));
        if (cmd[i + 1] != NULL)
            write(fd, " ", 1);
    }
    write(fd, "\n", 1);
    close(fd);
    return 1;
}
