/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <ncurses.h>
#include <stdlib.h>
#include "mysh.h"

void start_ncurses(void)
{
    setenv("TERM", "xterm-256color", 1);
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    ncurses_on_off(true);
}
