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
#include <sys/types.h>
#include <dirent.h>

// This function print the prompt. And a '~' for replace the home directory.
static char *find_branch_name(void)
{
    FILE *fp = popen("git branch | grep \"*\" | cut -d ' ' -f2", "r");
    char *branch = NULL;
    size_t len = 0;

    getline(&branch, &len, fp);
    branch[strlen(branch) - 1] = '\0';
    pclose(fp);
    return branch;
}

static void is_github_folder(char *pwd, char **env)
{
    char **arr = my_str_to_word_array(pwd, "/");
    char *home = my_getenv(env, "HOME");
    int len = my_arraylen(arr);
    DIR *dir = NULL;

    if (my_start_with(pwd, home) == true)
        len -= 2;
    for (int i = 0; i < len; i++) {
        dir = opendir(".git");
        if (dir != NULL) {
            my_putstr("\t\t\033[1;32m");
            my_putstr("git:(");
            my_putstr(find_branch_name());
            my_putstr(")\033[0m");
            closedir(dir);
            return;
        }
        chdir("..");
    }
    chdir(pwd);
}

static void print_arrow(int result_cmd)
{
    if (result_cmd == 0)
        my_putstr("\033[1;32m");
    else
        my_putstr("\033[1;31m");
    my_putstr("\n>\033[0m ");
}

int print_prompt(char **env, int result_cmd)
{
    char *home = my_getenv(env, "HOME");
    char *prompt = NULL;
    char *pwd = my_getpwd();

    if (isatty(0) == 0)
        return 0;
    if (my_start_with(pwd, home)) {
        prompt = strdup("~");
        prompt = realloc(prompt, strlen(prompt) + strlen(pwd));
        prompt = strcat(prompt, pwd + strlen(home));
    } else
        prompt = strdup(pwd);
    my_putstr("\033[1;34m");
    my_putstr(prompt);
    is_github_folder(pwd, env);
    print_arrow(result_cmd);
    free(prompt);
    free(pwd);
    return 0;
}
