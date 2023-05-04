/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

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
    //char ***penv;
    pipe_t *pipes;
} token_t;

typedef struct special_s {
    char *str;
    int len;
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
        {">", 1, REDIR_RIGHT},
        {"<", 1,REDIR_LEFT},
        {">>", 2, DOUBLE_REDIR_RIGHT},
        {"<<", 2, DOUBLE_REDIR_LEFT},
        {"|", 1, PIPE},
        {";", 1, SEMICOLON},
        {"&&", 2, AND},
        {"||", 2, OR},
        {NULL, 0, NONE}
};

#define TI token->index
#define TL token->line

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

void print_type(int type)
{
    switch (type) {
        case END:
            printf("END\n");
            break;
        case NONE:
            printf("NONE\n");
            break;
        case REDIR_RIGHT:
            printf("REDIR_RIGHT\n");
            break;
        case REDIR_LEFT:
            printf("REDIR_LEFT\n");
            break;
        case DOUBLE_REDIR_RIGHT:
            printf("DOUBLE_REDIR_RIGHT\n");
            break;
        case DOUBLE_REDIR_LEFT:
            printf("DOUBLE_REDIR_LEFT\n");
            break;
        case PIPE:
            printf("PIPE\n");
            break;
        case SEMICOLON:
            printf("SEMICOLON\n");
            break;
        case AND:
            printf("AND\n");
            break;
        case OR:
            printf("OR\n");
            break;
    }
}

void read_command(token_t *token)
{
    char **arr = malloc(sizeof(char*) * 1);
    arr[0] = NULL;
    do {
        arr_append(&arr, token->elem);
        get_token(token);
    } while (token->type == NONE);
    //exec_command(arr)
}

void parser(char *line)
{
    token_t *token = malloc(sizeof(token_t));
    token->line = line;
    token->index = 0;
    get_token(token);
    while (token->type != END) {
        read_command(token);
    }
    free(token);
}

int main(int ac, char **av)
{
    parser("ls -l || cat -e");
    return (0);
}
