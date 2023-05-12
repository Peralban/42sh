/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "parser.h"
#include <string.h>

token_t *token_dup(token_t *token)
{
    token_t *new = malloc(sizeof(token_t));

    if (new == NULL)
        return NULL;
    new->elem = NULL;
    new->type = token->type;
    new->index = token->index;
    new->line = token->line;
    new->error = token->error;
    new->exit = token->exit;
    return new;
}
