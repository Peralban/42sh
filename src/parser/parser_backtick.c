/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "my.h"
#include "mysh.h"
#include "parser.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static void exec_inside_backtick(char *line)
{
    int exitt = 0;
    int error = 0;
    int fd = open("/tmp/.42sh_backtick", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        exit(84);
    ncurses_on_off(0);
    dup2(fd, 1);
    close(fd);
    parser(line, &exitt, &error);
    exit(error);
}

static void create_arr_from_backtick(char ***arr)
{
    int fd = open("/tmp/.42sh_backtick", O_RDONLY);
    struct stat st;
    char *str = NULL;
    char **tmp = NULL;

    if (fd == -1)
        return;
    stat("/tmp/.42sh_backtick", &st);
    str = malloc(sizeof(char) * (st.st_size + 1));
    if (str == NULL)
        return;
    read(fd, str, st.st_size);
    str[st.st_size - 1] = '\0';
    tmp = my_str_to_word_array(str, "\n");
    for (int i = 0; tmp[i] != NULL; i++) {
        arr_append(arr, strdup(tmp[i]));
    }
    destroy_array(tmp);
    free(str);
    close(fd);
}

void parser_backtick(token_t *token, char ***arr)
{
    int start = token->index;
    int status = 0;

    get_token(token);
    while (token->type != BACKTICK) {
        get_token(token);
    }
    char *line = strndup(token->line + start, token->index - start - 1);
    pid_t pid = fork();
    if (pid == 0) {
        exec_inside_backtick(line);
    } else {
        waitpid(pid, &status, 0);
    }
    create_arr_from_backtick(arr);
    get_token(token);
}

void backtick_gestion(token_t *token)
{
    if (token->type == BACKTICK) {
        do {
            get_token(token);
        } while (token->type != BACKTICK);
        get_token(token);
    }
}
