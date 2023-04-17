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
    char **cmd = NULL;

    (void)ac;
    (void)av;
    while (!error) {
        if (getline(&line, &size, stdin) == -1) {
            my_exit(NULL, &error);
            break;
        }
        line[strlen(line) - 1] = '\0';
        cmd = my_str_to_word_array(line, " \t");
        if (built_in(cmd, env, &error) == 1)
            continue;
    }
    return 0;
}
