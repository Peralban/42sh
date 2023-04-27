/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_exit.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"
#include "my.h"

// A function that frees the memory allocated to the array of strings
// and print "exit". Also sets the error variable to 1. To break the main loop.
int my_exit(char **cmd, int *error)
{
    int len = my_arraylen(cmd);

    *error = -1;
    if (strcmp(cmd[0], "Error") != 0) {
        for (int i = 0; i < len; i++) {
            free(cmd[i]);
        }
        free(cmd);
    }
    if (isatty(0) == 1)
        my_putstr("exit\n");
    return 1;
}
