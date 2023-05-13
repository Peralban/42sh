/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#ifndef INC_42SH_REPO_SPECIAL_CHAR_H
    #define INC_42SH_REPO_SPECIAL_CHAR_H

    #include "parser.h"

typedef struct special_s {
    char *str;
    int len;
    int type;
} special_t;

const special_t special[] = {
        {">", 1, REDIR_RIGHT},
        {"<", 1,REDIR_LEFT},
        {">>", 2, DOUBLE_REDIR_RIGHT},
        {"<<", 2, DOUBLE_REDIR_LEFT},
        {"|", 1, PIPE},
        {";", 1, SEMICOLON},
        {"&&", 2, AND},
        {"||", 2, OR},
        {"`", 1, BACKTICK},
        {NULL, 0, NONE}
};

#endif //INC_42SH_REPO_SPECIAL_CHAR_H
