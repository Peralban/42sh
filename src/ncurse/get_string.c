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

static void add_char_to_line(int ch, char **save, char **line, int *index)
{
    int len = strlen(*line);

    (*line) = realloc(*line, sizeof(char) * (len + 2));
    if (*line == NULL)
        return;
    for (int i = len; i >= *index; i--)
        (*line)[i + 1] = (*line)[i];
    (*line)[*index] = (char)ch;
    (*line)[len + 1] = '\0';
    (*index)++;
    *save = strdup(*line);
}

static void remove_char_to_line(char **line, int *index)
{
    int len = strlen(*line);

    *line = realloc(*line, sizeof(char) * (len));
    if (*line == NULL)
        return;
    for (int i = *index - 1; i < len; i++)
        (*line)[i] = (*line)[i + 1];
    (*line)[len - 1] = '\0';
    (*index)--;
}

static void get_keyboard_event(int ch, char **save, char **line, int *index)
{
    if (ch == KEY_BACKSPACE && *index > 0) {
        remove_char_to_line(line, index);
    }
    if (PRINTABLE(ch)) {
        add_char_to_line(ch, save, line, index);
    }
    if (ch == 4) {
        free(*line);
        endwin();
        exit(0);
    }
    if (ch == 5)
        cmd_in_sublime(line);
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
    char **history = get_history_array();
    int history_index = my_arraylen(history);
    char *save = strdup(line);
    int index = 0;

    for (int ch = getch(); ch != 10; ch = getch()) {
        get_keyboard_event(ch, &save, &line, &index);
        if (ch == KEY_UP || ch == KEY_DOWN) {
            line = strdup(move_in_history(ch, save, &history_index, history));
            index = strlen(line);
        }
        display_term(term_name, line);
        if (ch == KEY_LEFT || ch == KEY_RIGHT)
            move_cursor(ch, line, &index);
        print_cursor(line, index);
    }
    free_history_and_save(history, save);
    return line;
}
