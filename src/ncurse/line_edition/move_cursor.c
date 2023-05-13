/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** move_cursor.c
*/

#include "mysh.h"
#include "my.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int move_cursor(int ch, char *line, size_t line_len, int *cursor_index)
{
    int y = 0;
    int x = 0;

    getyx(stdscr, y, x);
    if (ch == KEY_LEFT) {
        move(y, x - 1);
        *cursor_index -= 1;
    }
    if (ch == KEY_RIGHT) {
        move(y, x + 1);
        *cursor_index += 1;
    }
    return 0;
}
