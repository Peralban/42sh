/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_putstr.c
*/

#include <unistd.h>
#include <string.h>

void my_putstr(char *str)
{
    write(1, str, strlen(str));
}
