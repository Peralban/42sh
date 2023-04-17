/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** The mysh's include file
*/

#ifndef __mysh_H
    #define __mysh_H

int main(int ac, char **av, char **env);
int built_in(char **cmd, char **env, int *error);
void my_exit(char **cmd, int *error);

#endif
