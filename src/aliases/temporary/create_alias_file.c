/*
** EPITECH PROJECT, 2023
** create_alias_file.c
** File description:
** create the temporary file to store the not preset aliases
*/

#include "mysh.h"
#include "my.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void create_alias_file(char **env)
{
    char *home_path = my_getenv(env, "HOME");
    int fd = 0;

    if (home_path == NULL || env == NULL)
        return;
    fd = open("/.42sh_alias", O_CREAT | O_RDWR, 0664);
    if (fd == -1) {
        free(home_path);
        return;
    }
    free(home_path);
    close(fd);
}
