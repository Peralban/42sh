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
char *test_echo_special_cases(char *str);
int my_echo(char *line, int *error);
bool echo_execution(char *line, int *error);
char *find_special_char_last_cases(char c);
char *find_special_char(char c);
char *handle_backslash(char *str, char *new_str, int i, int j);
int my_setenv(char **args, char **env, int *return_value);
void variable_and_value(char **env, char **args);
void variable_only(char **env, char *variable);
int my_unsetenv(char **args, char **env, int *return_value);
int setup_env(char **env);
int parse_args_setenv(char **args);
char **set_env_tab(char **new_env);
char **get_env_tab(void);
void exec_parent(int pid, int *error);
void exec_redirections(const token_t *token);
int my_exec(char **cmd, char **env, token_t *token);
int check_access(char *cmd, bool *not_access);
char *get_tmp(char *path, char *cmd);
char *search_command(char *cmd, char **env, int *error);
void my_put_permission_denied(char *cmd);
void my_put_command_not_found(char *cmd);
char *check_usr_bin(char *cmd, int *error);
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
void start_ncurses(void);
char *move_in_history(int ch, char *save, int *index, char **history);
int ncurses_on_off(int on_off);
int is_ncurses(void);
char *get_string(char *term_name, char *line);
int read_command(token_t *token);
void skip_and_or(token_t *token);
void read_and_or(token_t *token);
void parser(char *line, int *exit, int *error);
int and_or_right_side(token_t *token);
void parsing_error_and_or(token_t *token);
void parsing_display_error(int code);
int parsing_error(token_t *token);
int pipe_right_side(token_t *token, int *nb_pipe);
void parsing_error_pipe(token_t *token);
void get_token_right(token_t *token);
void get_token_with_redir(token_t *token, int nb_pipe);
void set_token_type(token_t *token);
int is_special(token_t *token, int i);
void special_operand(token_t *token, int i, int k);
void set_token_elem(token_t *token);
void get_token(token_t *token);
token_t *token_dup(token_t *token);
void pipes_stuff_child(pipe_t *pipes, int right);
void multiple_pipe(token_t *token, pipe_t *pipes, int *status);
void read_pipe(token_t *token);
void set_redirection_name(token_t *token);
void reset_redir_name(token_t *token);
char *my_getenv(char **env, char *var);
void print_prompt(char **env, int result_cmd);
char *my_getpwd(void);
bool var_are_init(char **env);
int history(char *line, int *error);
char **get_history_array(void);
int get_term_fd(void);
int redirect_left(int fd, char *file_path);
int redirect_right(int fd);
int redirection(char *file_path, special_type_e type);
int double_left_redirection(char *brackets);
char *find_num_variable(char *str, char **wa, int i, char **env);
char *create_new_line(char *new_line, char *tmp, int size);
char *detect_variables(char *line, char **env, int *error);
char *get_var_value(char *str, int i);
char *get_var_name(char *str, int i);
int get_back_cmd(void);
char *join_all_args(char *str);
char *find_other_variable(char *str, char **wa, int i, char **env);
char *find_special_variable(char *str, int i, char **env, int *error);
void delete_local_variable(char *name);
void append_local_variable(char *name, char *value);
char *find_local_variable(char *str, int i);
int my_set(char **cmd, int *error);
int my_unset(char **cmd, int *error);
int cmd_in_sublime(char **line);

#endif
