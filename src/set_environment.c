/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set_environment.c
*/

#include "mysh.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <string.h>
#include "my.h"

// This function return the home directory.
static char *gethome(char *actual_pwd)
{
    char *home = NULL;
    char **array_pwd = my_str_to_word_array(actual_pwd, "/");

    if (strcmp(array_pwd[0], "home") == 0) {
        home = strdup("/");
        home = strcat(home, array_pwd[0]);
        home = strcat(home, "/");
        if (array_pwd[1] != NULL && strcmp(array_pwd[1], "lost+found") != 0)
            home = strcat(home, array_pwd[1]);
    }
    return home;
}

// This function set the environment variables [pwd, home, user and oldpwd].
static void set_environment(char *home)
{
    char **array_home = my_str_to_word_array(home, "/");
    char *usr = strdup(array_home[1]);
    char *pwd = my_getpwd();

    setenv("PWD", pwd, 1);
    setenv("HOME", home, 1);
    setenv("USER", usr, 1);
    setenv("OLDPWD", "", 1);
    free(pwd);
    free(usr);
    free(home);
}

// This function set the environment variables.
// It's call in the main function.
int setup_env(void)
{
    char *actual_pwd = my_getpwd();
    char *home = NULL;

    home = gethome(actual_pwd);
    set_environment(home);
    return 0;
}