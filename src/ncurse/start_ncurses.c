/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <ncurses.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mysh.h"

void start_ncurses(void)
{
    char *color = set_color_file("/tmp/.42sh_color");

    setenv("TERM", "xterm-256color", 1);
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    int fd = open(color, O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1)
        exit(84);
    close(fd);
    set_color_file(color);
    ncurses_on_off(true);
}

void end_ncurses(void)
{
    ncurses_on_off(false);
    endwin();
}
