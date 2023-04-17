/*
** EPITECH PROJECT, 2023
** my
** File description:
** The my's include file
*/

#include <stdbool.h>

#ifndef __my_H
    #define __my_H

bool my_start_with(char *src, char *cmp);
void my_putstr(char *str);
void arr_remove(char ***arr_p, int i);
void arr_append(char ***arr_p, char *elem);
bool isin(char c, char *delim);
char *my_strdupij(char *str, int begin, int end);
char **my_str_to_word_array(char *str, char *delim);
int my_arraylen(char **array);

#endif
