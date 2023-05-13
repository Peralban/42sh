/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** precise_cmd.c
*/

#include "mysh.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "my.h"

static int create_file(char *cmd)
{
    int fd = open(get_path("subl.txt"), O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        my_putstr("Error: can't create file\n");
        return 1;
    }
    write(fd, cmd, strlen(cmd));
    close(fd);
    return 0;
}

static char *get_str_in_file(char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat st;
    char *cmd = NULL;

    if (fd == -1)
        return NULL;
    stat(file, &st);
    cmd = malloc(sizeof(char) * (st.st_size + 1));
    if (cmd == NULL)
        return NULL;
    read(fd, cmd, st.st_size);
    cmd[st.st_size] = '\0';
    close(fd);
    return cmd;
}

static int execute_cmd_in_file(char **line)
{
    char *subl_path = get_path("subl.txt");
    int fd = open(subl_path, O_RDONLY, 0644);
    char *cmd = get_str_in_file(subl_path);

    if (cmd != NULL) {
        *line = strdup(cmd);
        free(cmd);
    }
    close(fd);
    remove(subl_path);
    return 0;
}

int cmd_in_sublime(char **line)
{
    int status = 0;
    pid_t pid = (pid_t) 0;

    if (create_file(*line) == 1)
        return 1;
    pid = fork();
    if (pid == 0) {
        if (execvp("subl", (char *[]){"subl", "-w", "subl.txt", NULL}) == -1) {
            my_puterror
            ("Error: Sublime Text is not installed on your computer.\n");
            exit(1);
        }
    } else {
        waitpid(pid, &status, 0);
    } if (WIFEXITED(status))
        if (WEXITSTATUS(status) == 1)
            return 1;
    return execute_cmd_in_file(line);
}
