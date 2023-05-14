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

void add_alias(char *line, int *error)
{
    int fd = get_alias_file_fd();
    char **cmd = my_str_to_word_array(line, " \t");
    int nb_args = my_arraylen(cmd);

    if (fd == -1) {
        *error = 1;
        return;
    }
    for (int i = 1; cmd[i] != NULL; i++) {
        if (i == 2 && nb_args > 3)
            write(fd, "(", 1);
        write(fd, cmd[i], strlen(cmd[i]));
        if (cmd[i + 1] != NULL)
            write(fd, " ", 1);
        if (nb_args > 3 && cmd[i + 1] == NULL)
            write(fd, ")", 1);
    }
    write(fd, "\n", 1);
    close(fd);
    return;
}
