/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** clear_screen.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

int clear_screen(void)
{
    char *path_to_term = get_path(".42sh_term");
    int fd = open(path_to_term, O_WRONLY | O_TRUNC);

    if (fd == -1) {
        return 1;
    }
    close(fd);
    free(path_to_term);
    return 0;
}
