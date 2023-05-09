/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"

void get_token_with_redir(token_t *token, int nb_pipe)
{
    get_token(token);
    if (token->type == REDIR_LEFT || token->type == DOUBLE_REDIR_LEFT) {
        get_token(token);
        if (token->type != NONE) {
            *token->error = 31;
            return;
        }
        if (token->left == true) {
            *token->error = 11;
            return;
        }
        if (nb_pipe > 0) {
            *token->error = 12;
            return;
        }
        token->left = true;
        get_token(token);
    }
    if (token->type == REDIR_RIGHT || token->type == DOUBLE_REDIR_RIGHT) {
        get_token(token);
        if (token->type != NONE) {
            *token->error = 32;
            return;
        }
        if (token->right == true) {
            *token->error = 21;
            return;
        }
        token->right = true;
        get_token(token);
    }
}

int pipe_right_side(token_t *token, int *nb_pipe)
{
    if (token->type == PIPE) {
        *nb_pipe += 1;
        if (token->right == true) {
            *token->error = 22;
            return 1;
        }
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
    token->right = false;
    token->left = false;
    int nb_pipe = 0;
    do {
        if (token->type == PIPE) {
            *token->error = 9;
            return;
        }
        while (token->type == NONE)
            get_token_with_redir(token, nb_pipe);
        if (pipe_right_side(token, &nb_pipe) == 1)
            return;
        if (*token->error != 0)
            return;
    }
    while (token->type == NONE);
}
