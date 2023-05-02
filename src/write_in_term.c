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

const char def_term_name_[] = "42sh_term";

void put_str_in_term(int fd, const char *str)
{
    if (isatty(0) == 0)
        write(fd, str, strlen(str));
    else {
        int fdp = open(def_term_name_, O_WRONLY | O_APPEND);
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
    char *str = malloc(sizeof(char) * 12);
    char tmp;
    int i = 0;

    if (nb == 0) {
        put_str_in_term(fd, "0");
        return;
    }
    for (; nb > 0; i++) {
        str[i] = (nb % 10) + '0';
        nb /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        tmp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = tmp;
    }
    put_str_in_term(fd, str);
    free(str);
}
