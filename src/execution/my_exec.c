/*
** EPITECH PROJECT, 2023
** my_exec.c
** File description:
** functions that execute the commands
*/

#include "my.h"
#include "mysh.h"
#include "parser.h"
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
            my_putstr("Interrupted");
            break;
        case SIGILL:
            my_putstr("Illegal inscruction");
            break;
        case SIGABRT:
            my_putstr("Abort");
            break;
        case SIGFPE:
            my_putstr("Floating exception");
            break;
        case SIGSEGV:
            my_putstr("Segmentation fault");
            break;
        case SIGTERM:
            my_putstr("Terminated");
            break;
    }
}

void exec_parent(int pid, int *error)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) != 0) {
        status_handling(status);
        if (WCOREDUMP(status) != 0)
            my_putstr(" (core dumped)");
        my_putstr("\n");
    }
    *error = WEXITSTATUS(status);
}

static void exec_child(char **cmd, char **env, char *new_cmd, token_t *token)
{
    pipe_t *pipes = token->pipes;

    pipes_stuff_child(pipes);
    if (execve(new_cmd, cmd, env) == -1) {
        my_puterror("Execve failed\n");
    }
}

int my_exec(char **cmd, char **env, token_t *token)
{
    pid_t pid = 0;
    char *new_cmd = NULL;
    int *error = token->error;

    if (cmd == NULL || error == NULL)
        return 0;
    new_cmd = search_command(cmd[0], env, error);
    if (new_cmd == NULL) {
        *error = 1;
        return 0;
    }
    pid = fork();
    if (pid == 0) {
        exec_child(cmd, env, new_cmd, token);
    } else {
        if (token->pipes->max == 0)
            exec_parent(pid, error);
    }
    return pid;
}
