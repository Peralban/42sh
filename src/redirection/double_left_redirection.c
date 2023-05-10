/*
** EPITECH PROJECT, 2023
** double_left_redirection.c
** File description:
** Contains the basic the double left redirection
*/

#include "mysh.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char **add_string(char **content, char *buffer)
{
    int len = my_arraylen(content);
    char **new_content = malloc(sizeof(char *) * (len + 2));

    if (new_content == NULL)
        return NULL;
    if (len != 0) {
        for (int i = 0; i < len; i++)
            new_content[i] = content[i];
    }
    new_content[len] = strdup(buffer);
    new_content[len + 1] = NULL;
    free(content);
    return new_content;
}

static char **get_content(char *brackets)
{
    char **content = NULL;
    char *term_name = get_term_name();
    char *buffer = NULL;

    my_putstr("? ");
    buffer = my_getline_ncurses(term_name);
    while (buffer != NULL) {
        if (strcmp(buffer, brackets) == 0)
            break;
        content = add_string(content, buffer);
        if (content == NULL)
            return NULL;
        my_putstr("? ");
        buffer = my_getline_ncurses(term_name);
    }
    free(buffer);
    return content;
}

static int print_in_term(int fd, char **content)
{
    char *file_path = strdup("/tmp/42sh");

    if (file_path == NULL)
        return 1;
    for (int i = 0; content[i] != NULL; i++) {
        write(fd, content[i], strlen(content[i]));
        write(fd, "\n", 1);
    }
    close(fd);
    return redirection(file_path, REDIR_LEFT);
}

int double_left_redirection(char *brackets)
{
    char **content = NULL;
    int fd = open("/tmp/42sh", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
        return 1;
    if (brackets == NULL) {
        my_puterror("Missing name for redirect.\n");
        close(fd);
        return 1;
    }
    content = get_content(brackets);
    if (content == NULL)
        return 0;
    return print_in_term(fd, content);
}
