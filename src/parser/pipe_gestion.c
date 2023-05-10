/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

void pipes_stuff_child(pipe_t *pipes, int right)
{
    int fd = 0;

    if (pipes->max > 0) {
        if (pipes->index > 0) {
            dup2(pipes->fds[pipes->index * 2 - 2], STDIN_FILENO);
        }
        if (pipes->index < pipes->max) {
            dup2(pipes->fds[pipes->index * 2 + 1], STDOUT_FILENO);
        }
        for (int i = 0; i < pipes->max * 2; i++) {
            close(pipes->fds[i]);
        }
    } if (pipes->index == pipes->max && is_ncurses() == true && right == 0) {
        fd = open(get_term_name(), O_RDWR | O_APPEND);
        if (fd == -1)
            exit(84);
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
    }
}

static void skip_redir(token_t *token)
{
    if (ANY_REDIR_TYPE(token->type)) {
        get_token(token);
        get_token(token);
    }
}

static pipe_t *set_pipes(token_t *token)
{
    pipe_t *pipe = malloc(sizeof(pipe_t));

    if (pipe == NULL)
        return NULL;
    pipe->max = 0;
    pipe->index = 0;
    while (token->type != SEMICOLON && token->type != END &&
    token->type != OR && token->type != AND) {
        if (token->type == PIPE) {
            pipe->max++;
        }
        skip_redir(token);
        get_token(token);
    }
    pipe->fds = malloc(sizeof(int) * pipe->max * 2);
    free(token);
    if (pipe->fds == NULL)
        return NULL;
    return pipe;
}

void multiple_pipe(token_t *token, pipe_t *pipes, int *status)
{
    int *pids = malloc(sizeof(int) * (pipes->max + 1));

    if (pids == NULL)
        return;
    pids[0] = read_command(token);
    for (pipes->index = 1; pipes->index <= pipes->max; pipes->index++) {
        get_token(token);
        pids[pipes->index] = read_command(token);
    }
    for (int i = 0; i < pipes->max * 2; i++) {
        close(pipes->fds[i]);
    }
    for (int i = 0; i < pipes->max + 1; i++) {
        exec_parent(pids[i], status);
    }
}

void read_pipe(token_t *token)
{
    pipe_t *pipes = set_pipes(token_dup(token));

    if (pipes == NULL) {
        while (token->type != SEMICOLON && token->type != END &&
        token->type != OR && token->type != AND)
            get_token(token);
        *token->error = -1;
        return;
    }
    for (int i = 0; i < pipes->max; i++)
        pipe(pipes->fds + i * 2);
    token->pipes = pipes;
    if (pipes->max == 0) {
        read_command(token);
    } else {
        multiple_pipe(token, pipes, token->error);
    }
    free(pipes->fds);
    free(pipes);
}
