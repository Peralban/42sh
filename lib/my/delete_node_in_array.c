/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** delete_node_in_array.c
*/

#include "my.h"

int delete_str_in_array(char **array, int index)
{
    int array_size = my_arraylen(array);
    int i = 0;

    while (i < array_size) {
        if (i >= index) {
            array[i] = array[i + 1];
        }
        i++;
    }
    return 0;
}
