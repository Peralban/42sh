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

int read_command(token_t *token)
{
    char **arr = malloc(sizeof(char*) * 1);
    int pid = 0;

    if (arr == NULL)
        return 0;
    arr[0] = NULL;
    do {
        arr_append(&arr, strdup(token->elem));
        get_token(token);
    } while (token->type == NONE);
    pid = exec_command(get_env_tab(), arr, token);
    free(arr);
    return pid;
}

void read_and_or(token_t *token)
{
    do {
        read_pipe(token);
        if (*token->error != 0 && token->type == AND) {
            while (token->type != END && token->type != SEMICOLON &&
            token->type != OR)
                get_token(token);
        }
        if (*token->error == 0 && token->type == OR) {
            while (token->type != END && token->type != SEMICOLON)
                get_token(token);
        }
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
    while (token->type != END) {
        while (token->type != END && token->type != SEMICOLON) {
            read_and_or(token);
        }
        get_token(token);
    }
    free(token);
}
