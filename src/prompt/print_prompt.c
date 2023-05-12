/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_cd.c
*/

#include "../../include/mysh.h"
#include "../../include/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

// This function print the prompt. And a '~' for replace the home directory.
static char *find_branch_name(void)
{
    FILE *fp = popen("cat .git/HEAD |  cut -d '/' -f3", "r");
    char *branch = NULL;
    size_t len = 0;

    if (fp == NULL)
        return "none";
    getline(&branch, &len, fp);
    branch[strlen(branch) - 1] = '\0';
    pclose(fp);
    return branch;
}

static void is_github_folder(char *pwd)
{
    char **arr = my_str_to_word_array(pwd, "/");
    int len = my_arraylen(arr);
    DIR *dir = NULL;

    for (int i = 0; i < len; i++) {
        dir = opendir(".git");
        if (dir != NULL) {
            my_putstr("        git:(");
            my_putstr(find_branch_name());
            my_putstr(")");
            closedir(dir);
            return;
        }
        chdir("..");
    }
}

void print_prompt(char **env, int result_cmd)
{
    char *home = my_getenv(env, "HOME");
    char *prompt = NULL;
    char *pwd = my_getpwd();

    if (is_ncurses() == false)
        return;
    if (home != NULL && my_start_with(pwd, home)) {
        my_putstr("~");
        my_putstr(pwd + strlen(home));
    } else {
        my_putstr(pwd);
    }
    is_github_folder(pwd);
    my_putstr("\n> ");
    chdir(pwd);
    free(prompt);
    free(pwd);
}
