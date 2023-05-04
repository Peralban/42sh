/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>

typedef struct pipe_s {
    int *fds;
    int max;
    int index;
} pipe_t;

typedef struct token_s {
    int index;
    int type;
    char *line;
    char *elem;
    char ***penv;
    pipe_t *pipes;
} token_t;

typedef struct special_s {
    char *str;
    int type;
} special_t;

typedef enum special_type_e {
    END = -1,
    NONE = 0,
    REDIR_RIGHT,
    REDIR_LEFT,
    DOUBLE_REDIR_RIGHT,
    DOUBLE_REDIR_LEFT,
    PIPE,
    SEMICOLON,
    AND,
    OR
} special_type_e;

const special_t special[] = {
    {">", REDIR_RIGHT},
    {"<", REDIR_LEFT},
    {">>", DOUBLE_REDIR_RIGHT},
    {"<<", DOUBLE_REDIR_LEFT},
    {"|", PIPE},
    {";", SEMICOLON},
    {"&&", AND},
    {"||", OR},
    {NULL, NONE}
};

#define TI token->index
#define TL token->line

void set_token_type(token_t *token)
{
    int i = 0;
    int j = 0;

    for (i = 0; special[i].str != NULL; i++) {
        for (j = 0; token->elem[j] == special[i].str[j]; j++);
        if (token->elem[j] == '\0' && special[i].str[j] == '\0') {
            token->type = special[i].type;
            return;
        }
    }
    token->type = NONE;
}

void get_token(token_t *token)
{
    int i = 0;
    int j = 0;

    token->elem = NULL;
    if (TL[TI] == '\0') {
        token->type = END;
        return;
    }
    for (;TL[TI] == ' ' || TL[TI] == '\t' || TL[TI] == '\0'; TI++);
    for (i = TI; TL[i] != ' ' && TL[i] != '\t' && TL[i] != '\0'; i++);
    token->elem = malloc(sizeof(char) * (i - TI + 1));
    if (token->elem == NULL)
        return;
    for (j = 0; TI < i; TI++, j++) {
        token->elem[j] = TL[TI];
    }
    token->elem[j] = '\0';
    set_token_type(token);
}

void parser(char *line)
{

}