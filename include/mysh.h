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

char *my_get_line(int *error, char *term_name);
void the_sh(char **env);
int main(int ac, char **av, char **env);
void destroy_array(char **arr);
int built_in(char **cmd, char **env, int *error);
int my_exit(int *error);
int my_cd(char **cmd, char **env, int *error);
char *adapt_str(char *str, int nb_quotes);
char *test_special_cases(char *str);
char *tab_to_str(char **cmd);
int my_echo(char **cmd, int *error);
char *find_special_char_last_cases(char c);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);
int my_setenv(char **args, char **env, int *return_value);
int my_unsetenv(char **args, char **env, int *return_value);
int setup_env(char **env);
int parse_args_setenv(char **args);
void my_exec(char **cmd, char **env, int *error);
char *search_command(char *cmd, char **env, int *error);
void my_put_permission_denied(char *cmd);
void my_put_command_not_found(char *cmd);
void print_from_the_end(char *buffer);
void print_term_bis(const char *line, char *buffer);
void display_term(char *term_name, char *line);
char *get_string(char *term_name, char *line);
char *my_getline_ncurses(char *term_name);
char *my_strdupij_endin(const char *str, int begin, int end);
void add_to_arr(char ***arr, char *str, int *swa);
void get_word(char *str, char *delim, char ***arr, int *swa);
void init_swa(int max_size, int *swa);
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
void start_ncurses(void);
char *my_getenv(char **env, char *var);
void print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
bool var_are_init(char **env);
void create_alias_file(char **env);
void add_alias(char **env, char **cmd);
void execute_alias(char **cmd, char **env, int *error);
char *get_cmd_from_alias(char **env, char *cmd);
char **get_alias_file(char **env);
int get_alias_file_fd(char **env);

#endif
