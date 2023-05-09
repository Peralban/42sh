/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#ifndef INC_42SH_REPO_PARSER_H
    #define INC_42SH_REPO_PARSER_H

    #include <stdlib.h>

    #define TI token->index
    #define TL token->line

typedef struct pipe_s {
    int *fds;
    int max;
    int index;
} pipe_t;

typedef struct redir_s {
    int type;
    char *name;
} redir_t;

typedef struct token_s {
    int index;
    int type;
    char *line;
    char *elem;
    int *exit;
    int *error;
    pipe_t *pipes;
    int right;
    int left;
    redir_t redir[2];
} token_t;

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

    #define ANY_REDIR_TYPE(type) \
    (type == REDIR_LEFT || type == DOUBLE_REDIR_LEFT || \
    type == REDIR_RIGHT || type == DOUBLE_REDIR_RIGHT)

#endif //INC_42SH_REPO_PARSER_H
