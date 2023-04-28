/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "../include/mysh.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

bool is_printable(int ch)
{
    if (ch >= 32 && ch <= 126)
        return true;
    return false;
}

const char prompt[] = "$[hello je suis un treeeeeeeeeeeeees long prompt]\n> ";

void print_from_the_end(char *buffer)
{
    char **arr = my_str_to_word_array_max_size(buffer, "\n", getmaxx(stdscr));
    int max_y = getmaxy(stdscr);
    int start = 0;
    int len = 0;

    for (; arr[len] != NULL; len++);
    if (len > max_y)
        start = len - max_y;
    for (int i = start; i < len; i++) {
        mvprintw(i - start, 0, arr[i]);
    }
}

void display_term(char *term_name, char *line)
{
    int read_fd = open(term_name, O_RDONLY);
    struct stat sb;
    stat(term_name, &sb);
    char *buffer = malloc(sizeof(char) * (sb.st_size + 1));
    read(read_fd, buffer, sb.st_size);
    buffer[sb.st_size] = '\0';
    close(read_fd);
    buffer = realloc(buffer, sizeof(char) * (strlen(buffer) + strlen(line) + 1));
    strcat(buffer, line);
    clear();
    print_from_the_end(buffer);
    free(buffer);
}

char *my_getline_ncurses(char *term_name)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);

    int fd = open(term_name, O_RDWR | O_APPEND);
    if (fd == -1)
        return NULL;
    write(fd, prompt, strlen(prompt));

    char *line = malloc(sizeof(char) * 1);
    if (line == NULL)
        return NULL;
    line[0] = '\0';
    int len = 0;

    display_term(term_name, line);
    for (int ch = getch(); ch != 10; ch = getch(), len = strlen(line)) {
        if (ch == KEY_BACKSPACE && len > 0) {
            line = realloc(line, sizeof(char) * (len));
            line[len - 1] = '\0';
        } if (is_printable(ch)) {
            line = realloc(line, sizeof(char) * (len + 2));
            line[len] = ch;
            line[len + 1] = '\0';
        }
        display_term(term_name, line);
    }
    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    close(fd);
    return line;
}

//int main(int argc, char **argv, char **env)
//{
//    char *str = NULL;
//    char *term_name = "tmp";
//
//    remove(term_name);
//    int fd = open(term_name, O_CREAT, 0666);
//    close(fd);
//    while (1) {
//        str = my_getline_ncurses(term_name);
//    }
//    remove(term_name);
//    return 0;
//}