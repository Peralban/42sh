/*
** EPITECH PROJECT, 2023
** get_alias.c
** File description:
** functions that get the alias file of the alias of the alias cmds
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

static get_cmd_from_array(char **line)
{
    char *cmd = NULL;
    int len = 0;

    for (int i = 1; line[i] != NULL; i++)
        len += strlen(line[i]) + 1;
    cmd = malloc(sizeof(char) * (len + 1));
    if (cmd == NULL) {
        destroy_array(line);
        return NULL;
    }
    cmd[0] = '\0';
    for (int i = 1; line[i] != NULL; i++) {
        strcat(cmd, line[i]);
        if (line[i + 1] != NULL)
            strcat(cmd, " ");
    }
    destroy_array(line);
    return cmd;
}

char *get_cmd_from_alias(char *cmd)
{
    char **alias_list = get_alias_file();
    char **line = NULL;

    if (alias_list == NULL)
        return NULL;
    for (int i = 0; alias_list[i] != NULL; i++) {
        line = my_str_to_word_array(alias_list[i], "\t()");
        if (strcmp(line[0], cmd) == 0) {
            destroy_array(alias_list);
            return get_cmd_from_array(line);
        }
        destroy_array(line);
    }
    destroy_array(alias_list);
    return NULL;
}

char **get_alias_file(void)
{
    char **alias = NULL;
    int fd = get_alias_file_fd();
    char *buffer = NULL;
    struct stat st;

    if (fd == -1)
        return NULL;
    stat("/tmp/.42sh_aliases", &st);
    buffer = malloc(sizeof(char) * (st.st_size + 1));
    if (read(fd, buffer, st.st_size) == -1) {
        free(buffer);
        close(fd);
        return NULL;
    }
    buffer[st.st_size] = '\0';
    alias = my_str_to_word_array(buffer, "\n()");
    free(buffer);
    close(fd);
    return alias;
}

int get_alias_file_fd(void)
{
    int fd = open("/tmp/.42sh_aliases", O_CREAT | O_APPEND | O_RDWR, 0664);

    return fd;
}
