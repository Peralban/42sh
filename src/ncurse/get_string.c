/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** get_string.c
*/

#include "mysh.h"
#include "my.h"
#include "my_getline.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static void get_keyboard_event(int ch, char **save, char **line, size_t len)
{
    if (ch == KEY_BACKSPACE && len > 0) {
        *line = realloc(*line, sizeof(char) * (len));
        if (*line == NULL)
            return;
        (*line)[len - 1] = '\0';
    }
    if (PRINTABLE(ch)) {
        (*line) = realloc(*line, sizeof(char) * (len + 2));
        if (*line == NULL)
            return;
        (*line)[len] = (char)ch;
        (*line)[len + 1] = '\0';
        *save = strdup(*line);
    }
    if (ch == 4) {
        free(*line);
        exit(0);
    }
}

static void free_history_and_save(char **history, char *save)
{
    if (history != NULL)
        destroy_array(history);
    if (save != NULL)
        free(save);
}

char *get_string(char *term_name, char *line)
{
    size_t len = 0;
    char **history = get_history_array();
    int history_index = my_arraylen(history);
    char *save = strdup(line);

    for (int ch = getch(); ch != 10; ch = getch(), len = strlen(line)) {
        get_keyboard_event(ch, &save, &line, len);
        if (ch == KEY_UP || ch == KEY_DOWN)
            line = strdup(move_in_history(ch, save, &history_index, history));
        display_term(term_name, line);
    }
    free_history_and_save(history, save);
    return line;
}
