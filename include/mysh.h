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
    #include <unistd.h>
    #include "parser.h"

typedef struct token_s token_t;
typedef struct pipe_s pipe_t;

char *my_get_line(char *term_name, int *exit_value);
int exec_command(char **env_cpy, char **cmd, token_t *token);
void the_sh(char **env);
int main(int ac, char **av, char **env);
char *get_path(char *file_name);
void destroy_array(char **arr);
int built_in(char **cmd, char **env, int *error, int *exit_value);
int my_exit(int *exit_value);
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
char *gethome(char *actual_pwd);
int setup_env(char **env);
int parse_args_setenv(char **args);
char **set_env_tab(char **new_env);
char **get_env_tab(void);
void exec_parent(int pid, int *error);
int my_exec(char **cmd, char **env, token_t *token);
char *search_command(char *cmd, char **env, int *error);
void my_put_permission_denied(char *cmd);
void my_put_command_not_found(char *cmd);
void print_from_the_end(char *buffer);
void print_term_bis(const char *line, char *buffer);
void display_term(char *term_name, char *line);
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
char *create_term_name(void);
void start_ncurses(void);
char *move_in_history(int ch, char *save, int *index, char **history);
int ncurses_on_off(int on_off);
int is_ncurses(void);
char *get_string(char *term_name, char *line);
int read_command(token_t *token);
void read_and_or(token_t *token);
void parser(char *line, int *exit, int *error);
int pipe_right_side(token_t *token);
void parsing_error_pipe(token_t *token);
int and_or_right_side(token_t *token);
void parsing_error_and_or(token_t *token);
void parsing_display_error(int code);
int parsing_error(token_t *token);
void set_token_type(token_t *token);
int is_special(token_t *token, int i);
void special_operand(token_t *token, int i, int k);
void set_token_elem(token_t *token);
void get_token(token_t *token);
token_t *token_dup(token_t *token);
void pipes_stuff_child(pipe_t *pipes);
void multiple_pipe(token_t *token, pipe_t *pipes, int *status);
void read_pipe(token_t *token);
char *my_getenv(char **env, char *var);
void print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
bool var_are_init(char **env);
int history(char *line, int *error);
char **get_history_array(void);
int get_term_fd(void);
int right_redirection(char *file_path, special_type_e type);
int double_left_redirection(char *brackets, char **args);

#endif
