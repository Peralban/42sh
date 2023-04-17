/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** The mysh's include file
*/

#ifndef __mysh_H
    #define __mysh_H

int main(int ac, char **av, char **env);
char *my_getenv(char **env, char *str);
int print_prompt(void);
char *my_getpwd(void);
int setup_env(void);

#endif
