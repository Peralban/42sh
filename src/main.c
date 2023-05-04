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

char *my_get_line(int *error, char *term_name)
{
    char *line = NULL;
    size_t size = 0;

    if (isatty(0) == 0 || getenv("TERM") == NULL) {
        if (getline(&line, &size, stdin) < 0) {
            my_exit(error);
            return NULL;
        }
        line[strlen(line) - 1] = '\0';
    } else {
        line = my_getline_ncurses(term_name);
        if (line == NULL) {
            my_exit(error);
            return NULL;
        }
    }
    return line;
}

static void loop(char **env_cpy)
{
    char **cmd = NULL;
    char *line = NULL;
    int error = 0;

    while (error != -1) {
        print_prompt(env_cpy, error);
        error = 0;
        line = my_get_line(&error, get_term_name());
        if (line == NULL || line[0] == '\0')
            continue;
        if (history(line, &error) == 1)
            continue;
        cmd = my_str_to_word_array(line, " \t");
        free(line);
        if (built_in(cmd, env_cpy, &error) == 2)
            my_exec(cmd, env_cpy, &error);
        destroy_array(cmd);
    }
}

void the_sh(char **env)
{
    char **env_cpy = my_arraydup(env);
    char *def_term_name = set_term_name(".42sh_term");
    int fd = 0;

    remove(def_term_name);
    fd = open(def_term_name, O_CREAT, 0666);
    if (fd == -1)
        return;
    close(fd);

    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    loop(env_cpy);
    remove(def_term_name);
}

int main(int ac, char **av, char **env)
{
    if (isatty(0) == 1)
        start_ncurses();
    the_sh(env);
    if (isatty(0) == 1)
        endwin();
    return 0;
}
