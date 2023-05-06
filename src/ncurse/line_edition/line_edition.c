/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** line_edition.c
*/

#include "mysh.h"
#include "my.h"
#include <ncurses.h>
#include <string.h>

char *history_up_and_down(int ch, char *save, int *index, char **history)
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
    } else if (ch == KEY_DOWN) {
        if (*index >= len && save != NULL) {
            line = save;
            return line;
        }
        if (*index < len) {
            (*index)++;
            line = strdup(history[*index]);
        }
    }
    return line;
}
