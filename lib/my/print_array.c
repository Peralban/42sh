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
#include <string.h>

int print_array(char **array)
{
    int str_size = 0;

    for (int i = 0; array[i] != NULL; i++) {
        str_size = strlen(array[i]);
        my_putstr(array[i]);
        if (array[i][str_size - 1] != '\n')
            my_putstr("\n");
    }
    return 0;
}
