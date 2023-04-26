/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "../include/mysh.h"
#include "../include/my.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct vector_s {
    int x;
    int y;
} vector_t;

typedef struct cursor_s {
    vector_t pos;
    vector_t max;
    vector_t base;
} cursor_t;

bool is_printable(int ch)
{
    if (ch >= 32 && ch <= 126)
        return true;
    return false;
}

const char prompt[] = "$ hello je suis un treeeeeeeeeeeeees long prompt> ";

void check_resize(cursor_t *cursor, vector_t prompt_pos, char *str)
{
    if (cursor->max.x != getmaxx(stdscr) || cursor->max.y != getmaxy(stdscr)) {
        cursor->max.x = getmaxx(stdscr);
        cursor->max.y = getmaxy(stdscr);
        clear();
        mvprintw(prompt_pos.y, prompt_pos.x, prompt);
        cursor->base.x = getcurx(stdscr);
        cursor->base.y = getcury(stdscr);
        mvprintw(cursor->base.y, cursor->base.x, str);
        cursor->pos.y = getcurx(stdscr);
        cursor->pos.y = getcury(stdscr);
    }
    //encore des bug de resize a corriger le curseur ne se deplace pas correctement
    //les anciennes lignes disparraissent
    //revoir la position initial de la ligne pour la re-afficher
}

char *my_getline_ncurses(void)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);

    vector_t prompt_pos = {getcurx(stdscr), getcury(stdscr)};
    printw(prompt);
    cursor_t *cursor = malloc(sizeof(cursor_t));
    cursor->pos.x = getcurx(stdscr);
    cursor->pos.y = getcury(stdscr);
    cursor->max.x = getmaxx(stdscr);
    cursor->max.y = getmaxy(stdscr);
    cursor->base.x = getcurx(stdscr);
    cursor->base.y = getcury(stdscr);
    move(cursor->pos.y, cursor->pos.x);
    char *str = malloc(sizeof(char) * 1);
    if (str == NULL)
        return NULL;
    str[0] = '\0';
    int len = 0;
    for (int ch = getch(); ch != 10; ch = getch()) {
        check_resize(cursor, prompt_pos, str);
        len = strlen(str);
        if (ch == KEY_BACKSPACE && len > 0) {
            cursor->pos.x--;
            if (cursor->pos.x < 0) {
                cursor->pos.x = getmaxx(stdscr) - 1;
                cursor->pos.y--;
                move(cursor->pos.y, cursor->pos.x);
            }
            mvdelch(cursor->pos.y, cursor->pos.x);
            str = realloc(str, sizeof(char) * (len));
            str[len - 1] = '\0';
        } if (is_printable(ch)) {
            str = realloc(str, sizeof(char) * (len + 2));
            str[len] = ch;
            str[len + 1] = '\0';
            mvprintw(cursor->pos.y, cursor->pos.x, "%c", ch);
            cursor->pos.x++;
            if (cursor->pos.x >= getmaxx(stdscr)) {
                cursor->pos.x = 0;
                cursor->pos.y++;
                move(cursor->pos.y, cursor->pos.x);
            }
        }
    }
    cursor->pos.y++;
    cursor->pos.x = 0;
    move(cursor->pos.y, cursor->pos.x);
    endwin();
    return str;
}

int main(int argc, char **argv, char **env)
{
    char *str = NULL;
    while (1) {
        str = my_getline_ncurses();
    }
    free(str);
    return 0;
}