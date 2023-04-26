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
    char **env_cpy = my_arraydup(env);
    int result_cmd = 0;

    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    while (!error) {
        print_prompt(env_cpy, result_cmd);
        if (getline(&line, &size, stdin) == -1)
            my_exit((char *[2]){"Error", NULL}, &error);
        line[strlen(line) - 1] = '\0';
        cmd = my_str_to_word_array(line, " \t");
        if (built_in(cmd, env_cpy, &error) != 2)
            continue;
    }
    return 0;
}
