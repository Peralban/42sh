/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "mysh.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

char **create_command(token_t *token, char **arr)
{
    do {
        if (ANY_REDIR_TYPE(token->type)) {
            set_redirection_name(token);
            continue;
        }
        if (token->type == BACKTICK) {
            parser_backtick(token, &arr);
            continue;
        }
        arr_append(&arr, strdup(token->elem));
        get_token(token);
    } while (token->type == NONE || ANY_REDIR_TYPE(token->type) ||
    token->type == BACKTICK);
    return arr;
}

int read_command(token_t *token)
{
    char **arr = malloc(sizeof(char*) * 1);
    int pid = 0;

    if (arr == NULL)
        return 0;
    arr[0] = NULL;
    reset_redir_name(token);
    arr = create_command(token, arr);
    pid = exec_command(get_env_tab(), arr, token);
    free(arr);
    return pid;
}

void skip_and_or(token_t *token)
{
    if (*token->error != 0 && token->type == AND) {
        while (token->type != END && token->type != SEMICOLON &&
        token->type != OR)
            get_token(token);
    }
    if (*token->error == 0 && token->type == OR) {
        while (token->type != END && token->type != SEMICOLON)
            get_token(token);
    }
}

void read_and_or(token_t *token)
{
    *token->error = 0;
    while (token->type == AND) {
        get_token(token);
    }
    if (token->type == END || token->type == SEMICOLON)
        return;
    do {
        if (token->type == AND)
            break;
        read_pipe(token);
        skip_and_or(token);
        get_token(token);
    }
    while (token->type == AND || token->type == OR);
}

void parser(char *line, int *exit, int *error)
{
    token_t *token = malloc(sizeof(token_t));

    if (token == NULL)
        return;
    token->line = line;
    token->elem = NULL;
    token->index = 0;
    token->exit = exit;
    token->error = error;
    get_token(token);
    if (parsing_error(token_dup(token)) != 0) {
        return;
    }
    while (token->type != END) {
        while (token->type != END && token->type != SEMICOLON) {
            read_and_or(token);
        }
        get_token(token);
    }
    free(token);
}
