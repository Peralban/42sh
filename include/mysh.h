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

char *my_get_line(char *term_name, int *exit_value);
void the_sh(char **env);
int main(int ac, char **av, char **env);
int built_in(char **cmd, char **env, int *error, int *exit_value);
int parse_args_setenv(char **args);
int my_unsetenv(char **args, char **env, int *return_value);
int my_setenv(char **args, char **env, int *return_value);
int my_exit(int *error);
char *adapt_str(char *str, int nb_quotes);
char *test_special_cases(char *str);
char *tab_to_str(char **cmd);
int my_echo(char **cmd, int *error);
char *find_special_char_last_cases(char c);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);
int my_cd(char **cmd, char **env, int *error);
char *gethome(char *actual_pwd);
int setup_env(char **env);
char *my_getenv(char **env, char *var);
void print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
bool var_are_init(char **env);
void destroy_array(char **arr);
void print_from_the_end(char *buffer);
void print_term_bis(const char *line, char *buffer);
void display_term(char *term_name, char *line);
char *get_string(char *term_name, char *line);
char *my_getline_ncurses(char *term_name);
char *my_strdupij_endin(const char *str, int begin, int end);
void add_to_arr(char ***arr, char *str, int *swa);
void get_word(char *str, char *delim, char ***arr, int *swa);
char **my_str_to_word_array_max_size(char *str, char *delim, int max_size);
void put_str_in_term(int fd, const char *str);
void put_array_in_term(int fd, char **arr);
void put_number_in_term(int fd, int nb);
void my_putstr(const char *str);
void my_putnbr(int nb);
void print_array(char **arr);
void my_puterror(const char *str);
char *set_term_name(char *name);
char *get_term_name(void);
char *create_term_name(void);
void start_ncurses(void);

#endif
