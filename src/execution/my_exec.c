/*
** EPITECH PROJECT, 2023
** my_exec.c
** File description:
** functions that execute the commands
*/

#include "my.h"
#include "mysh.h"
#include "command_error_handling.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static void status_handling(int status)
{
    switch (WTERMSIG(status)) {
        case SIGINT:
            my_puterror("Interrupted");
            break;
        case SIGILL:
            my_puterror("Illegal inscruction");
            break;
        case SIGABRT:
            my_puterror("Abort");
            break;
        case SIGFPE:
            my_puterror("Floating exception");
            break;
        case SIGSEGV:
            my_puterror("Segmentation fault");
            break;
        case SIGTERM:
            my_puterror("Terminated");
            break;
    }
}

static void exec_parent(int pid, int *error)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) != 0) {
        status_handling(status);
        if (WCOREDUMP(status) != 0)
            my_puterror(" (core dumped)");
        my_puterror("\n");
    }
    *error = WEXITSTATUS(status);
}

static void exec_child(char **cmd, char **env, int *error, char *new_cmd)
{
    int fd = 0;

    fd = open(get_term_name(), O_RDWR | O_APPEND);
    if (fd == -1)
        exit(84);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    if (execve(new_cmd, cmd, env) == -1) {
        my_put_command_not_found(cmd[0]);
        *error = 1;
    }
    exit(0);
}

void my_exec(char **cmd, char **env, int *error)
{
    pid_t pid = 0;
    char *new_cmd = NULL;

    if (cmd == NULL || error == NULL)
        return;
    new_cmd = search_command(cmd[0], env, error);
    if (new_cmd == NULL)
        return;
    pid = fork();
    if (pid == 0) {
        exec_child(cmd, env, error, new_cmd);
    } else {
        exec_parent(pid, error);
    }
}
