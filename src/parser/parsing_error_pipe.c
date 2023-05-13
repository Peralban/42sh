/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"

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
        while (token->type == NONE || ANY_REDIR_TYPE(token->type) ||
        token->type == BACKTICK) {
            get_token(token);
            get_token_with_redir(token, nb_pipe);
        }
        if (pipe_right_side(token, &nb_pipe) == 1)
            return;
        if (*token->error != 0)
            return;
    }
    while (token->type == NONE);
}
