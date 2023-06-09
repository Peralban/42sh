/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** main.c
*/

#include "../include/mysh.h"
#include "../include/my.h"
#include "parser.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

char *my_get_line(char *term_name, int *exit_value)
{
    char *line = NULL;
    size_t size = 0;

    if (is_ncurses() == 0) {
        if (getline(&line, &size, stdin) < 0) {
            my_exit(exit_value);
            return NULL;
        }
        line[strlen(line) - 1] == '\n' ? line[strlen(line) - 1] = '\0' : 0;
    } else {
        line = my_getline_ncurses(term_name);
        if (line == NULL) {
            my_exit(exit_value);
            return NULL;
        }
    }
    return line;
}

int exec_command(char **env_cpy, char **cmd, token_t *token)
{
    int *error = token->error;
    int *exit_value = token->exit;

    if (built_in(&cmd, env_cpy, error, exit_value) == 2)
        return my_exec(cmd, env_cpy, token);
    return *error;
}

static void loop(void)
{
    char *line = NULL;
    int error = 0;
    int exit_value = 0;

    while (exit_value != 1) {
        print_prompt(get_env_tab(), error);
        error = 0;
        line = my_get_line(get_term_name(), &exit_value);
        if (line == NULL || line[0] == '\0')
            continue;
        line = detect_variables(line, get_env_tab(), &error);
        parser(line, &exit_value, &error);
        free(line);
        if (is_ncurses() == true)
            fill_color_file();
    }
}

void the_sh(char **env)
{
    char **env_cpy = my_arraydup(env);
    char *def_term_name = set_term_name(get_path(".42sh_term"));
    int fd = 0;

    set_env_tab(env_cpy);
    remove(def_term_name);
    fd = open(def_term_name, O_CREAT, 0666);
    if (fd == -1)
        return;
    close(fd);
    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    loop();
    remove(def_term_name);
}

int main(int ac, char **av, char **env)
{
    if (ac != 1 || av[0] == NULL)
        return 84;
    if (sizeof(void *) == 4)
        return 84;
    if (isatty(0) == 1)
        start_ncurses();
    else
        ncurses_on_off(0);
    the_sh(env);
    if (is_ncurses() == true) {
        end_ncurses();
    }
    return 0;
}
