/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <../include/mysh.h>

void my_putstr(const char *str)
{
    put_str_in_term(1, str);
}

void my_putnbr(int nb)
{
    put_number_in_term(1, nb);
}

void print_array(char **arr)
{
    put_array_in_term(1, arr);
}

void my_puterror(const char *str)
{
    put_str_in_term(2, str);
}