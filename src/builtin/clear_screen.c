/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** clear_screen.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

static void print_usage(void)
{
    my_putstr("Usage: clear [OPTION]\n\n\n");
    my_putstr("Options:\n");
    my_putstr("\t-T TERM\tuse this instead of $TERM\n");
    my_putstr("\t-V\tprint curses-version\n");
    my_putstr("\t-x\tdo not try to clear scrollback\n");
}

static int clear_option(char **cmd)
{
    if (cmd[1][0] == '-') {
        if (strcmp(cmd[1], "-h") == 0) {
            print_usage();
            return 0;
        } if (strcmp(cmd[1], "-V") == 0) {
            my_putstr("ncurses version ");
            my_putstr(NCURSES_VERSION);
            my_putstr("\n");
            return 0;
        } if (strcmp(cmd[1], "-x") == 0) {
            my_putstr("clear: -x option not implemented yet.\n");
            return 0;
        } if (strcmp(cmd[1], "-T") == 0) {
            my_putstr("clear: -T option not implemented yet.\n");
            return 0;
        }
        my_puterror("clear: Invalid option.\n");
    }
    print_usage();
    return 1;
}

int clear_screen(char **cmd)
{
    int array_size = my_arraylen(cmd);
    char *path_to_term = get_path(".42sh_term");
    int fd = 0;

    if (array_size > 2) {
        my_puterror("clear: Too many arguments.\n");
        print_usage();
        return 1;
    }
    if (array_size == 2)
        return clear_option(cmd);
    fd = open(path_to_term, O_WRONLY | O_TRUNC);
    if (fd == -1)
        return 1;
    close(fd);
    free(path_to_term);
    return 0;
}
