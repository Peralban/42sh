/*
** EPITECH PROJECT, 2023
** my
** File description:
** The my's include file
*/

#include <stdbool.h>

#ifndef __my_H
    #define __my_H

int delete_str_in_array(char **array, int index);
int my_arraylen(char **array);
int print_array(char **array);
bool my_start_with(char *src, char *cmp);
void arr_remove(char ***arr_p, int i);
char **my_str_to_word_array(char *str, char *delim);
void my_putstr(char *str);
bool char_isnum(char c);
void my_puterror(char *str);
char **my_arraydup(char **src);
bool char_isalpha(char c);
bool str_isalphanum(char *str);

#endif
