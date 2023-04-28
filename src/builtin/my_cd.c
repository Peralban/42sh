/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_cd.c
*/

#include "mysh.h"
#include "my.h"
#include <string.h>
#include <unistd.h>

static int print_error(char *cmd, int msg, int *error)
{
    char *error_msg[2] = {
        ": Too many arguments.\n",
        ": No such file or directory.\n"
    };

    my_puterror(cmd);
    my_puterror(error_msg[msg]);
    *error = 1;
    return 1;
}

static int cd_in_directory(char **cmd, char **env, int *error)
{
    char *set_pwd[4] = {"setenv", strdup("PWD"), NULL, NULL};
    char *set_oldpwd[4] =
    {"setenv", strdup("OLDPWD"), my_getenv(env, "OLDPWD"), NULL};

    if (chdir(cmd[1]) == -1) {
        return print_error(cmd[1], 1, error);
    } else {
        set_pwd[2] = my_getpwd();
        my_setenv(set_pwd, env, (int *) {0});
        my_setenv(set_oldpwd, env, (int *) {0});
    }
    return 1;
}

static int cd_in_home_directory(char **env, int *error)
{
    char *home = my_getenv(env, "HOME");
    char *set_pwd[4] = {"setenv", strdup("PWD"), NULL, NULL};
    char *oldpwd[4] =
    {"setenv", strdup("OLDPWD"), my_getenv(env, "PWD"), NULL};

    if (chdir(home) == -1) {
        return print_error("", 1, error);
    } else {
        set_pwd[2] = home;
        my_setenv(set_pwd, env, (int *) {0});
        my_setenv(oldpwd, env, (int *) {0});
    }
    return 1;
}

static int cd_in_oldpwd_directory(char **env, int *error)
{
    char *oldpwd = my_getenv(env, "OLDPWD");
    char *set_pwd[4] = {"setenv", strdup("PWD"), NULL, NULL};
    char *set_oldpwd[4] =
    {"setenv", strdup("OLDPWD"), my_getenv(env, "PWD"), NULL};

    if (oldpwd == NULL) {
        return print_error("", 1, error);
    } else {
        chdir(oldpwd);
        set_pwd[2] = oldpwd;
        my_setenv(set_pwd, env, (int *) {0});
        my_setenv(set_oldpwd, env, (int *) {0});
    }
    return 1;
}

int my_cd(char **cmd, char **env, int *error)
{
    int cmd_len = my_arraylen(cmd);

    if (cmd_len > 2)
        return print_error(cmd[0], 0, error);
    if (cmd_len == 1)
        return cd_in_home_directory(env, error);
    if (strcmp(cmd[1], "-") == 0)
        return cd_in_oldpwd_directory(env, error);
    return cd_in_directory(cmd, env, error);
}
