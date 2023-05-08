/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_getpwd.c
*/

#include "mysh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// This function return the current working directory with a perfect sizeof.
char *my_getpwd(void)
{
    char *tmp_pwd = malloc(sizeof(char) * 1024);
    char *pwd = NULL;

    if (tmp_pwd == NULL)
        return NULL;
    getcwd(tmp_pwd, 1024);
    pwd = strdup(tmp_pwd);
    return pwd;
}
