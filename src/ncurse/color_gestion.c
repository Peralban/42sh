/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"
#include "my_getline.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void fill_color_file(void)
{
    int fd = open(get_color_file(), O_WRONLY | O_APPEND);
    int fdp = open(get_term_name(), O_RDONLY);
    struct stat sb;
    struct stat sb2;

    if (fd == -1 || fdp == -1)
        return;
    stat(get_color_file(), &sb);
    stat(get_term_name(), &sb2);
    for (int i = sb.st_size; i < sb2.st_size; i++)
        write(fd, "1", 1);
    close(fd);
    close(fdp);
}

void fill_color_line(const char *line)
{
    int fdc = open(get_color_file(), O_WRONLY | O_APPEND);

    if (line[0] == '\0')
        write(fdc, "0", 1);
    for (int i = 0; line[i] != '\0'; i++)
        write(fdc, "1", 1);
    close(fdc);
}

char **get_color_arr(char *buffer)
{
    int fdc = open(get_color_file(), O_RDONLY);
    char *color = NULL;
    struct stat sb;

    stat(get_color_file(), &sb);
    color = malloc(sizeof(char) * (sb.st_size + strlen(buffer) + 1));
    if (color == NULL || fdc == -1)
        return NULL;
    read(fdc, color, sb.st_size);
    for (int i = 0; buffer[i] != '\0'; i++)
        color[i + sb.st_size] = WHITE;
    color[strlen(buffer)] = '\0';
    close(fdc);
    return my_str_to_word_array_max_size_model(buffer, "\n",
    getmaxx(stdscr), color);
}
