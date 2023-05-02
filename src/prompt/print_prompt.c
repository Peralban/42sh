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
            my_putstr("        git:(");
            my_putstr(find_branch_name());
            my_putstr(")");
            closedir(dir);
            return;
        }
        chdir("..");
    }
    chdir(pwd);
}

void print_prompt(char **env, int result_cmd)
{
    char *home = my_getenv(env, "HOME");
    char *prompt = NULL;
    char *pwd = my_getpwd();

    if (isatty(0) == 0)
        return;
    if (my_start_with(pwd, home)) {
        my_putstr("~");
        my_putstr(pwd + strlen(home));
    } else {
        my_putstr(pwd);
    }
    is_github_folder(pwd, env);
    my_putstr("\n> ");
    free(prompt);
    free(pwd);
}

//char *prompt_to_str(char **env)
//{
//    char *home = my_getenv(env, "HOME");
//    char *prompt = NULL;
//    char *pwd = my_getpwd();
//
//    if (my_start_with(pwd, home)) {
//        prompt = malloc(sizeof(char) * (strlen(pwd) - strlen(home) + 1));
//        prompt[0] = '~';
//        prompt[1] = '\0';
//        strcat(prompt, pwd + strlen(home));
//    } else {
//        prompt = strdup(pwd);
//    }
//    free(pwd);
//    free(home);
//    return prompt;
//}
//