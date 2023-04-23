/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** print_array.c
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <stdbool.h>

int print_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        my_putstr(array[i]);
        my_putstr("\n");
    }
    return 0;
}
