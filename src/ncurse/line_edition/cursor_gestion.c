/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <ncurses.h>
#include <string.h>

void print_cursor(char *line, int index)
{
    int len = strlen(line);
    int y = getcury(stdscr);
    int x = getcurx(stdscr);
    int max_x = getmaxx(stdscr);

    for (int i = len; i > index; i--) {
        x--;
        if (x < 0) {
            x = max_x - 1;
            y--;
        }
    }
    move(y, x);
}

void move_cursor(int ch, char *line, int *index)
{
    int len = strlen(line);

    if (ch == KEY_LEFT && *index > 0) {
        (*index)--;
    }
    if (ch == KEY_RIGHT && *index < len) {
        (*index)++;
    }
}
