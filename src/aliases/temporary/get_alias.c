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

char *get_cmd_from_alias(char **env, char *cmd)
{
    char **alias = get_alias_file(env);
    char *alias_cmd = NULL;

    if (alias == NULL)
        return NULL;
    for (int i = 0; alias[i] != NULL; i++) {
        if (strncmp(alias[i], cmd, strlen(cmd)) == 0) {
            alias_cmd = strdup(alias[i]);
            break;
        }
    }
    destroy_array(alias);
    return alias_cmd;
}

char **get_alias_file(char **env)
{
    int fd = get_alias_file_fd(env);
    char *home_path = my_getenv(env, "HOME");
    char *alias_path = NULL;
    char *buffer = NULL;
    char **alias = NULL;
    struct stat stats;

    alias_path = malloc(sizeof(char) * (strlen(home_path) + 12));
    if (fd == -1 || home_path == NULL || alias_path == NULL)
        return NULL;
    alias_path = strcpy(alias_path, home_path);
    alias_path = strcat(alias_path, "/.42sh_alias");
    stat(alias_path, &stats);
    read(fd, buffer, stats.st_size);
    alias = my_str_to_word_array(buffer, "\n");
    close(fd);
    free(home_path);
    free(alias_path);
    free(buffer);
    return alias;
}

int get_alias_file_fd(char **env)
{
    char *home_path = my_getenv(env, "HOME");
    int fd = 0;

    if (home_path == NULL || env == NULL)
        return -1;
    fd = open("/.42sh_alias", O_RDWR);
    free(home_path);
    return fd;
}
