/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "../include/mysh.h"
#include "../include/my_getline.h"

//here are all the functions that print in the terminal

void my_putstr(const char *str)
{
    put_str_in_term(1, str, WHITE);
}

void my_putnbr(int nb)
{
    put_number_in_term(1, nb, WHITE);
}

void print_array(char **arr)
{
    put_array_in_term(1, arr, WHITE);
}

void my_puterror(const char *str)
{
    put_str_in_term(2, str, WHITE);
}

void my_putstr_color(const char *str, char color)
{
    put_str_in_term(1, str, color);
}
