/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** The mysh's include file
*/

#include <stdbool.h>

#ifndef __mysh_H
    #define __mysh_H

    #include <stddef.h>

char *my_get_line(void);
int main(int ac, char **av, char **env);
int built_in(char **cmd, char **env, int *error);
void destroy_array(char **arr);
void print_from_the_end(char *buffer);
void display_term(char *term_name, char *line);
char *get_string(char *term_name, char *line);
void start_ncurses(void);
char *my_getline_ncurses(char *term_name, char *prompt);
char *my_strdupij_endin(const char *str, int begin, int end);
void add_to_arr(char ***arr, char *str, int *swa);
void get_word(char *str, char *delim, char ***arr, int *swa);
char **my_str_to_word_array_max_size(char *str, char *delim, int max_size);
int parse_args_setenv(char **args);
int my_unsetenv(char **args, char **env, int *return_value);
int my_setenv(char **args, char **env, int *return_value);
int my_exit(char **cmd, int *error);
char *my_getenv(char **env, char *var);
int print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
int setup_env(char **env);
bool var_are_init(char **env);
int my_cd(char **cmd, char **env, int *error);

//put stuff in terminal
void put_str_in_term(int fd, char *str);
void put_array_in_term(int fd, char **arr);
void put_number_in_term(int fd, int nb);


//built-in echo functions
int my_echo(char **cmd, int *error);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);

#endif
