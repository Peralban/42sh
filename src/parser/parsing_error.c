/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"

// error handling

int and_or_right_side(token_t *token)
{
    if (token->type == AND || token->type == OR) {
        get_token(token);
        if (token->type != NONE) {
            *token->error = 2;
            return 1;
        }
    }
    return 0;
}

void parsing_error_and_or(token_t *token)
{
    while (token->type == AND) {
        get_token(token);
    }
    do {
        if (token->type == AND || token->type == OR) {
            *token->error = 1;
            return;
        }
        parsing_error_pipe(token);
        if (and_or_right_side(token) == 1)
            return;
    }
    while (token->type == AND || token->type == OR);
}

// code 1: "(null) || cmd" error 'Invalid null command.'
// code 2: "cmd || (null)" error 'Invalid null command.'
// code 8: "cmd | (null)" error 'Invalid null command.'
// code 9: "(null) | cmd" error 'Invalid null command.'
//
// code: 11 "cmd < file < file" error 'Ambiguous input redirect.'
// code: 12 "cmd | cmd < file" error 'Ambiguous input redirect.'
// code: 21 "cmd > file > file" error 'Ambiguous output redirect.'
// code: 22 "cmd > file | cmd" error 'Ambiguous output redirect.'
// code: 31 "cmd < (null)" error 'Missing name for redirect.'
// code: 32 "cmd > (null)" error 'Missing name for redirect.'
//
void parsing_display_error(int code)
{
    if (code >= 1 && code < 10)
        my_putstr("Invalid null command.\n");
    if (code >= 11 && code < 20)
        my_putstr("Ambiguous input redirect.\n");
    if (code >= 21 && code < 30)
        my_putstr("Ambiguous output redirect.\n");
    if (code >= 31 && code < 40)
        my_putstr("Missing name for redirect.\n");
}

int parsing_error(token_t *token)
{
    int error = 0;
    if (token == NULL)
        return -1;
    while (token->type != END && *token->error == 0) {
        while (token->type != END && token->type != SEMICOLON &&
        *token->error == 0) {
            parsing_error_and_or(token);
        }
        get_token(token);
    }
    error = *token->error;
    free(token);
    parsing_display_error(error);
    return error;
}
