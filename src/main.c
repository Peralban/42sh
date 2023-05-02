/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** main.c
*/

#include "../include/mysh.h"
#include "../include/my.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

const char def_term_name[] = "42sh_term";

char *my_get_line(int *error)
{
    char *line = NULL;
    size_t size = 0;

    if (isatty(0) == 0) {
        if (getline(&line, &size, stdin) < 0) {
            my_exit((char *[2]){"Error", NULL}, error);
            return NULL;
        }
        line[strlen(line) - 1] = '\0';
    } else {
        line = my_getline_ncurses(def_term_name);
        if (line == NULL) {
            my_exit((char *[2]) {"Error", NULL}, error);
            return NULL;
        }
    }
    return line;
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    int error = 0;
    char **cmd = NULL;
    char **env_cpy = my_arraydup(env);

    (void)ac;
    (void)av;

    remove(def_term_name);
    int fd = open(def_term_name, O_CREAT, 0666);
    close(fd);

    if (isatty(0) == 1) {
        start_ncurses();
    }
    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    while (error != -1) {
        print_prompt(env_cpy, error);
        error = 0;
        line = my_get_line(&error);
        if (line == NULL || line[0] == '\0')
            continue;
        cmd = my_str_to_word_array(line, " \t");
        free(line);
        if (built_in(cmd, env_cpy, &error) != 2)
            continue;
        destroy_array(cmd);
    }
    if (isatty(0) == 1)
        endwin();
    remove(def_term_name);
    return 0;
}
