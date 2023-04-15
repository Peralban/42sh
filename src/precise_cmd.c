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

static void create_file(char *cmd)
{
    int fd = open("subl.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    write(fd, cmd, strlen(cmd));
    close(fd);
}

static char *get_str_in_file(char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat st;
    char *cmd = NULL;

    stat(file, &st);
    cmd = malloc(sizeof(char) * (st.st_size + 1));
    read(fd, cmd, st.st_size);
    cmd[st.st_size] = '\0';
    while (cmd[strlen(cmd) - 1] == '\n')
        cmd[strlen(cmd) - 1] = '\0';
    close(fd);
    return cmd;
}

static char **execute_cmd_in_file(void)
{
    int fd = open("subl.txt", O_RDONLY, 0644);
    pid_t pid = (pid_t) 0;
    char *cmd = get_str_in_file("subl.txt");
    char **sublime_cmd = NULL;

    //print_prompt(env);
    printf("?> %s\n", cmd);
    sublime_cmd = my_str_to_word_array(cmd, " \t\n");
    free(cmd);
    //my_exec(sublime_cmd, env);
    pid = fork();
    if (pid == 0) {
        if (execvp(sublime_cmd[0], sublime_cmd) == -1) {
            my_puterror(sublime_cmd[0]);
            my_puterror(": Command not found.\n");
            exit(1);
        }
        exit(0);
    } else {
        waitpid(pid, NULL, 0);
    }
    close(fd);
    remove("subl.txt");
    return sublime_cmd;
}

char **see_precise_cmd(char *cmd)
{
    int status = 0;
    pid_t pid = (pid_t) 0;

    create_file(cmd);
    pid = fork();
    if (pid == 0) {
        if (execvp("subl", (char *[]){"subl", "-wn", "subl.txt", NULL}) == -1) {
            my_puterror
            ("Error: Sublime Text is not installed on your computer.\n");
            exit(1);
        }
        exit(0);
    } else {
        waitpid(pid, &status, 0);
    } if (WIFEXITED(status))
        if (WEXITSTATUS(status) == 1)
            return NULL;
    return execute_cmd_in_file();
}
