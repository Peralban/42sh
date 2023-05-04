/*
** EPITECH PROJECT, 2023
** double_left_redirection.c
** File description:
** Contains the basic the double left redirection
*/

#include "mysh.h"
#include <stdio.h>

void handle_double_left_redirection(char **cmd, char **env, int *error)
{
    FILE *fd = tmpfile();

    if (fd == NULL) {
        *error = 1;
        return;
    }
    
}