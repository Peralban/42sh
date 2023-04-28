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
#include <fcntl.h>

const char prompt[] = "$[hello je suis un treeeeeeeeeeeeees long prompt]\n> ";
const char def_term_name[] = "42sh_term";

char *my_get_line(void)
{
    char *line = NULL;
    size_t size = 0;

    if (isatty(0) == 0) {
        if (getline(&line, &size, stdin) < 0) {
            return NULL;
        }
        line[strlen(line) - 1] = '\0';
    } else {
        line = my_getline_ncurses(def_term_name, prompt);
    }
    return line;
}

static char *my_getline(int *error)
{
    char *line = NULL;

    if (getline(&line, &size, stdin) == -1) {
        my_exit((char *[2]){"Error", NULL}, error);
        return NULL;
    }
    line[strlen(line) - 1] = '\0';
    return line;
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    int error = 0;
    char **cmd = NULL;
    char **env_cpy = my_arraydup(env);

    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    while (error != -1) {
        print_prompt(env_cpy, error);
        error = 0;
        line = my_getline(&error);
        if (line == NULL)
            continue;
            -----------------
    (void)ac;
    (void)av;
    remove(def_term_name);
    int fd = open(def_term_name, O_CREAT, 0666);
    close(fd);
    while (!error) {
        line = my_get_line();
        if (line == NULL)
            break;
            -------------------
        cmd = my_str_to_word_array(line, " \t");
        free(line);
        if (built_in(cmd, env_cpy, &error) != 2)
            continue;
        destroy_array(cmd);
    }
    remove(def_term_name);
    return 0;
}
