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

static char **get_content(char **args, char *brackets)
{
    char **content = my_arraydup(args);
    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, STDIN_FILENO) != -1) {
        if (strcmp(buffer, brackets) == 0)
            break;
        content = add_string(content, buffer);
        if (content == NULL)
            return NULL;
    }
    return content;
}

static int print_in_term(char **content)
{
    int fd = STDIN_FILENO;

    if (is_ncurses() == true)
            fd = get_term_fd();
    if (fd == -1)
        return 1;
    dup2(fd, STDIN_FILENO);
    for (int i = 0; content[i] != NULL; i++)
        my_putstr(content[i]);
    return 0;
}

int double_left_redirection(char *brackets, char **args)
{
    char **content = NULL;

    if (brackets == NULL) {
        my_puterror("Missing name for redirect.\n");
        return 1;
    }
    content = get_content(args, brackets);
    if (args != NULL)
        destroy_array(args);
    if (content == NULL)
        return 0;
    return print_in_term(content);
}
