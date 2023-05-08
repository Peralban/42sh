/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** get_file_path.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

//This function is used to get the path of a file
//It takes a file name as parameter
//It returns the path of the file to open it in the root of the project
char *get_path(char *file_name)
{
    char *path = NULL;
    static char *pwd = NULL;

    if (pwd == NULL)
        pwd = my_getpwd();
    path = malloc(sizeof(char) * (strlen(pwd) + strlen(file_name) + 2));
    if (pwd == NULL || file_name == NULL || path == NULL)
        return NULL;
    path[0] = '\0';
    path = strcat(path, pwd);
    path = strcat(path, "/");
    path = strcat(path, file_name);
    return path;
}
