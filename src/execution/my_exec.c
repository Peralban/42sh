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
#include <sys/stat.h>
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
    struct stat st;

    pipes_stuff_child(pipes, token->right);
    if (execve(new_cmd, cmd, env) == -1) {
        if (stat(cmd[0], &st) == 0 && !S_ISREG(st.st_mode)) {
        my_puterror(cmd[0]);
        my_puterror(": Is a directory.\n");
        exit(1);
    }
        my_puterror(cmd[0]);
        my_puterror(": Command not found.\n");
        exit(1);
    }
}

void exec_redirections(const token_t *token)
{
    if (token->left)
        redirection(token->redir[0].name, token->redir[0].type);
    if (token->right)
        redirection(token->redir[1].name, token->redir[1].type);
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
        exec_redirections(token);
        exec_child(cmd, env, new_cmd, token);
    } else {
        if (token->pipes->max == 0)
            exec_parent(pid, error);
    }
    return pid;
}
