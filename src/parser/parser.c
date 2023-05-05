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

void read_command(token_t *token)
{
    char **arr = malloc(sizeof(char*) * 1);

    if (arr == NULL)
        return;
    arr[0] = NULL;
    do {
        arr_append(&arr, strdup(token->elem));
        get_token(token);
    } while (token->type == NONE);
    exec_command(get_env_tab(), arr, token->error, token->exit);
    free(arr);
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
            read_command(token);
        }
        get_token(token);
    }
    free(token);
}
