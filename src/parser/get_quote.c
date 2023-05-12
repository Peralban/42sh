/*
** EPITECH PROJECT, 2023
** get_quote.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include "parser.h"
#include <string.h>

char *get_quote(token_t *token)
{
    char sign = TL[TI];

    token->type = NONE;
    for (int i = TI + 1; TL[i] != '\0'; i++) {
        if (TL[i] == sign) {
            token->elem = strndup(TL + TI, i - TI + 1);
            TI = i + 1;
            return token->elem;
        }
    }
    token->elem = NULL;
    if (sign == '\"')
        *token->error = 51;
    else
        *token->error = 52;
    return NULL;
}
