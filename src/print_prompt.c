/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_cd.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// This function print the prompt. And a '~' for replace the home directory.
int print_prompt(void)
{
    char *prompt = NULL;
    char *pwd = my_getpwd();
    char *home = getenv("HOME");

    if (isatty(0) == 0)
        return 0;
    if (my_start_with(pwd, home)) {
        prompt = strdup("~");
        prompt = realloc(prompt, strlen(prompt) + strlen(pwd) + 1);
        prompt = strcat(prompt, pwd + strlen(home));
    } else {
        prompt = strdup(pwd);
    }
    prompt = strcat(prompt, "\n> ");
    my_putstr(prompt);
    free(prompt);
    free(pwd);
    return 0;
}
