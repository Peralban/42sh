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
int my_unsetenv(char **args, char **env);
int my_setenv(char **args, char **env);
int my_exit(char **cmd, int *error);
char *my_getenv(char **env, char *var);
int print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
int setup_env(char **env);
bool var_are_init(char **env);

#endif
