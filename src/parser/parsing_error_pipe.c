/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"

int pipe_right_side(token_t *token)
{
    if (token->type == PIPE) {
        get_token(token);
        if (token->type != NONE) {
            *token->error = 8;
            return 1;
        }
    }
    return 0;
}

void parsing_error_pipe(token_t *token)
{
    do {
        if (token->type == PIPE) {
            *token->error = 9;
            return;
        }
        while (token->type == NONE)
            get_token(token);
        if (pipe_right_side(token) == 1)
            return;
    }
    while (token->type == NONE);
}
