/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** main.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av, char **env)
{
    size_t size = 0;
    char *line = NULL;
    int error = 0;

    (void) ac;
    (void) av;
    (void) env;
    setup_env();
    while (!error) {
        // print_prompt();
        if (getline(&line, &size, stdin) == -1) {
            break;
        }
        for (int i = 0; i < my_arraylen(env); i++)
            printf("%s\n", env[i]);
    }
    return 0;
}
