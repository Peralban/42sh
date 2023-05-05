/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "parser.h"
#include <string.h>
#include <special_char.h>

void set_token_type(token_t *token)
{
    int i = 0;

    for (i = 0; special[i].str != NULL; i++) {
        if (strcmp(token->elem, special[i].str) == 0) {
            token->type = special[i].type;
            return;
        }
    }
    token->type = NONE;
}

int is_special(token_t *token, int i)
{
    int j = 0;
    int count = 0;

    for (j = 0; special[j].str != NULL; j++) {
        if (strncmp(TL + i, special[j].str, special[j].len) == 0 &&
            special[count].len <= special[j].len) {
            count = j;
        }
    }
    return count;
}

void special_operand(token_t *token, int i, int k)
{
    if (i == TI) {
        token->elem = strndup(TL + TI, special[k].len);
        TI += special[k].len;
    } else {
        token->elem = strndup(TL + TI, i - TI);
        TI = i;
    }
}

void set_token_elem(token_t *token)
{
    int k = 0;

    for (int i = TI; TL[i] != '\0'; i++) {
        if (TL[i] == ' ' || TL[i] == '\t') {
            token->elem = strndup(TL + TI, i - TI);
            TI = i;
            break;
        }
        k = is_special(token, i);
        if (k > 0) {
            special_operand(token, i, k);
            break;
        }
        if (TL[i + 1] == '\0') {
            token->elem = strndup(TL + TI, i - TI + 1);
            TI = i + 1;
            break;
        }
    }
}

void get_token(token_t *token)
{
    free(token->elem);
    token->elem = NULL;
    for (;TL[TI] == ' ' || TL[TI] == '\t' || TL[TI] == '\0'; TI++) {
        if (TL[TI] == '\0') {
            token->type = END;
            return;
        }
    }
    set_token_elem(token);
    set_token_type(token);
}
