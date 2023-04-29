/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** The mysh's include file
*/

#include <stdbool.h>

#ifndef __mysh_H
    #define __mysh_H

int main(int ac, char **av, char **env);
int built_in(char **cmd, char **env, int *error);
int parse_args_setenv(char **args);
int my_unsetenv(char **args, char **env, int *return_value);
int my_setenv(char **args, char **env, int *return_value);
int my_exit(char **cmd, int *error);
char *my_getenv(char **env, char *var);
int print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
int setup_env(char **env);
bool var_are_init(char **env);
int history(char *line, int *error);
int my_cd(char **cmd, char **env, int *error);

//built-in echo functions
int my_echo(char **cmd, int *error);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);

#endif
