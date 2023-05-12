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
