/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** parse_args_setenv.c
*/

#include "my.h"
#include "mysh.h"

//Function to check if the array gived is good
int parse_args_setenv(char **args)
{
    if (char_isnum(args[1][0]) == 1) {
        my_puterror("setenv: Variable name must begin with a letter.\n");
        return 1;
    } if (str_isalphanum(args[1]) == 0) {
        my_puterror("setenv: Variable name must"
        " contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}
