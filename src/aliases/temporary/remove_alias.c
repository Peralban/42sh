/*
** EPITECH PROJECT, 2023
** remove_alias.c
** File description:
** functions to remove aliases
*/

#include "mysh.h"
#include "my.h"
#include <stdio.h>
#include <sys/stat.h>

static int is_not_in_file(char *line, int fd, int *error)
{
    char **aliases = get_alias_file();
    char **line_array = my_str_to_word_array(line, " \t");
    int len = -1;

    for (int i = 0; aliases[i] != NULL; i++) {
        if (strcmp(aliases[i], line_array[1]) == 0) {
            len = strlen(aliases[i]);
            destroy_array(aliases);
            destroy_array(line_array);
            return len;
        }
    }
    destroy_array(aliases);
    destroy_array(line_array);
    close(fd);
    return -1;
}

static void remove_file(int fd)
{
    close(fd);
    remove("/tmp/.42sh_aliases");
}

static void create_new_file(char *buffer, int index, int fd, int *error)
{
    int new_fd = 0;
    char **buffer_tab = NULL;

    remove_file(fd);
    new_fd = get_alias_file_fd();
    if (new_fd == -1) {
        *error = 1;
        return;
    }
    buffer_tab = my_str_to_word_array(buffer, "\n");
    for (int i = 0; buffer_tab[i] != NULL; i++) {
        if (i != index) {
            write(new_fd, buffer_tab[i], strlen(buffer_tab[i]));
            write(new_fd, "\n", 1);
        }
    }
    destroy_array(buffer_tab);
    close(new_fd);
}

static int get_linelen(char *line, int index)
{
    int len = 0;
    char **tmp = my_str_to_word_array(line, " \n");

    len = strlen(tmp[index]) + 1;
    destroy_array(tmp);
    return len;
}

void remove_alias(char *line, int *error)
{
    int fd = get_alias_file_fd();
    char *buffer = NULL;
    struct stat st;
    int index = -1;

    if (strcmp(line, "*") == 0)
        return remove_file(fd);
    index = is_not_in_file(line, fd, error);
    if (fd == -1 || index == -1) {
        *error = 1;
        return;
    }
    stat("/tmp/.42sh_aliases", &st);
    buffer = malloc(sizeof(char) * (st.st_size - get_linelen(line, index) + 1));
    if (buffer == NULL) {
        *error = 1;
        return;
    }
    read(fd, buffer, st.st_size);
    create_new_file(buffer, index, fd, error);
}
