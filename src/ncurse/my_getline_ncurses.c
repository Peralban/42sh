/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
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

void print_from_the_end(char *buffer)
{
    char **arr = my_str_to_word_array_max_size(buffer, "\n", getmaxx(stdscr));
    int max_y = getmaxy(stdscr);
    int start = 0;
    int len = 0;

    if (arr == NULL)
        return;
    for (; arr[len] != NULL; len++);
    if (len > max_y)
        start = len - max_y;
    for (int i = start; i < len; i++) {
        mvprintw(i - start, 0, "%s", arr[i]);
    }
    destroy_array(arr);
}

void print_term_bis(const char *line, char *buffer)
{
    char *tmp = realloc(buffer, sizeof(char) *
    (strlen(buffer) + strlen(line) + 1));
    if (tmp == NULL) {
        free(buffer);
        return;
    }
    strcat(tmp, line);
    clear();
    print_from_the_end(tmp);
    free(tmp);
}

void display_term(char *term_name, char *line)
{
    int read_fd = open(term_name, O_RDONLY);
    struct stat sb;
    char *buffer = NULL;

    stat(term_name, &sb);
    buffer = malloc(sizeof(char) * (sb.st_size + 1));
    if (buffer == NULL || read(read_fd, buffer, sb.st_size) < 0)
        return;
    buffer[sb.st_size] = '\0';
    close(read_fd);
    print_term_bis(line, buffer);
}

char *get_string(char *term_name, char *line)
{
    size_t len = 0;
    char **history = get_history_array();
    int history_index = my_arraylen(history);
    char *save = strdup(line);
    for (int c = getch(); c != 10; c = getch(), len = strlen(line)) {
        if (c == KEY_BACKSPACE && len > 0) {
            line = realloc(line, sizeof(char) * (len));
            line[len - 1] = '\0';
        } if (PRINTABLE(c)) {
            line = realloc(line, sizeof(char) * (len + 2));
            line[len] = (char)c;
            line[len + 1] = '\0';
            free(save);
            save = strdup(line);
        } if (c == KEY_UP || c == KEY_DOWN)
            line = strdup(line_edition(c, save, &history_index, history));
        display_term(term_name, line);
    }
    free_line_edition(history, save);
    return line;
}

char *my_getline_ncurses(char *term_name)
{
    int fd = open(term_name, O_RDWR | O_APPEND);
    char *line = malloc(sizeof(char) * 1);

    if (fd == -1 || line == NULL)
        return NULL;
    line[0] = '\0';
    display_term(term_name, line);
    line = get_string(term_name, line);
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
