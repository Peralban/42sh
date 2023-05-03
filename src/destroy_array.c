/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>

void destroy_array(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
