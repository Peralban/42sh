/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "parser.h"
#include "mysh.h"

void get_token_right(token_t *token)
{
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
    }
}

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
        return;
    }
    get_token_right(token);
}
