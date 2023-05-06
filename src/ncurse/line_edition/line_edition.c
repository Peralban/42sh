/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** line_edition.c
*/

#include "mysh.h"
#include "my.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static char *move_in_history(char *save, int *index, char **history, int ch)
{
    int len = my_arraylen(history) - 1;
    char *line = NULL;

    if (ch == KEY_UP) {
        if (*index == 0)
            *index = 1;
        if (*index > 0) {
            (*index)--;
            line = strdup(history[*index]);
        }
    } if (ch == KEY_DOWN) {
        if (*index >= len && save != NULL)
            line = save;
        if (*index < len) {
            (*index)++;
            line = strdup(history[*index]);
        }
    }
    return line;
}

char *line_edition(int ch, char *save, int *index, char **history)
{
    char *line = NULL;

    if (ch == KEY_UP || ch == KEY_DOWN)
        line = move_in_history(save, index, history, ch);
    return line;
}

void free_line_edition(char **history, char *save)
{
    destroy_array(history);
    free(save);
}
