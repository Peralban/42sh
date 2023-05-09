/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"
#include <string.h>

void set_redirection_name(token_t *token)
{
    if (token->type == REDIR_LEFT || token->type == DOUBLE_REDIR_LEFT) {
        token->left = 1;
        token->redir[0].type = token->type;
        get_token(token);
        token->redir[0].name = strdup(token->elem);
    } else if (token->type == REDIR_RIGHT ||
    token->type == DOUBLE_REDIR_RIGHT) {
        token->right = 1;
        token->redir[1].type = token->type;
        get_token(token);
        token->redir[1].name = strdup(token->elem);
    }
    get_token(token);
}

void reset_redir_name(token_t *token)
{
    token->right = 0;
    token->left = 0;
    token->redir[0].type = 0;
    token->redir[1].type = 0;
    token->redir[0].name = NULL;
    token->redir[1].name = NULL;
}
