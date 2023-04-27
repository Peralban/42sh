/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** The mysh's include file
*/

#ifndef __mysh_H
    #define __mysh_H

int main(int ac, char **av, char **env);
int built_in(char **cmd, char **env, int *error);
int parse_args_setenv(char **args);
int my_unsetenv(char **args, char **env);
int my_setenv(char **args, char **env);

//built-in echo functions
int my_echo(char **cmd, int *error);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);

#endif
