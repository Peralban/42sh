/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mysh.h"

void put_str_in_term(int fd, const char *str)
{
    int fdp = 0;

    if (is_ncurses() == false)
        write(fd, str, strlen(str));
    else {
        fdp = open(get_term_name(), O_WRONLY | O_APPEND);
        if (fdp == -1)
            return;
        write(fdp, str, strlen(str));
        close(fdp);
    }
}

void put_array_in_term(int fd, char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        put_str_in_term(fd, arr[i]);
        put_str_in_term(fd, "\n");
    }
}

void put_number_in_term(int fd, int nb)
{
    char *str = NULL;

    if (nb < 0) {
        put_str_in_term(fd, "-");
        nb = nb * -1;
    }
    if (nb > 9) {
        put_number_in_term(fd, nb / 10);
        put_number_in_term(fd, nb % 10);
    } else {
        str = malloc(sizeof(char) * 2);
        if (str == NULL)
            return;
        str[1] = '\0';
        str[0] = nb + '0';
        put_str_in_term(fd, str);
        free(str);
    }
}
