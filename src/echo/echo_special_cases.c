/*
** EPITECH PROJECT, 2023
** echo_special_cases.c
** File description:
** for 42sh
*/

#include "mysh.h"
#include <string.h>

char *find_special_char_last_cases(char c)
{
    switch (c) {
        case 'r':
            return "\r";
        case 't':
            return "\t";
        case 'n':
            return "\n";
        case 'v':
            return "\v";
        case '\\':
            return "\\";
        default:
            return strcat("\\", &c);
    }
}

char *find_special_char(char c)
{
    switch (c) {
        case 'a':
            return "\a";
        case 'b':
            return "\b";
        case 'c':
            return "\0";
        case 'e':
        case 'E':
            return "\e";
        case 'f':
            return "\f";
        default:
            return find_special_char_last_cases(c);
    }
}

char *handle_backslash(char *str, char *new_str, int i, int j)
{
    char *tmp = NULL;

    tmp = find_special_char(str[i + 1]);
        if (strlen(tmp) == 2) {
            new_str[j] = tmp[0];
            new_str[j + 1] = tmp[1];
            j++;
        } else
            new_str[j] = tmp[0];
    i++;
    j++;
    return new_str;
}
