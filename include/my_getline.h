/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#ifndef INC_42SH_REPO_MY_GETLINE_H
    #define INC_42SH_REPO_MY_GETLINE_H

    #define PRINTABLE(ch) (ch >= 32 && ch <= 126)

typedef enum swa_e {
    SWA_BEGIN,
    SWA_END,
    SWA_I,
    SWA_N,
    SWA_K,
    SWA_MAX
} swa_e;

typedef enum color_e {
    WHITE = '1',
    BLACK,
    RED,
    GREEN,
    BLUE,
    COLOR_MAX
} color_e;

char **my_str_to_word_array_max_size_model(char *model, char *delim,
int max_size, char *src);

#endif //INC_42SH_REPO_MY_GETLINE_H
