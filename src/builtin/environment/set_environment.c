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

// This function set the environment variables [pwd and oldpwd].
int setup_env(char **env)
{
    char *pwd = my_getpwd();
    char *setenv_cmd[2][4] = {
        {"setenv", strdup("OLDPWD"), strdup(""), NULL},
        {"setenv", strdup("PWD"), pwd, NULL}
    };

    for (int i = 0; i < 2; i++) {
        my_setenv(setenv_cmd[i], env, (int *) {0});
        env = get_env_tab();
    }
    set_env_tab(env);
    free(pwd);
    return 0;
}
