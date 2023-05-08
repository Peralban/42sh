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
bool my_start_with(char *src, char *cmp);
char *my_strdupij(char *str, int begin, int end);
bool isin(char c, char *delim);
void arr_append(char ***arr_p, char *elem);
char **my_str_to_word_array(char *str, char *delim);
bool char_isnum(char c);
char **my_arraydup(char **src);
bool char_isalpha(char c);
bool str_isalphanum(char *str);

#endif
