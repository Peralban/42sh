/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_exit.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"
#include "my.h"

// A function that frees the memory allocated to the array of strings
// and print "exit". Also sets the error variable to 1. To break the main loop.
int my_exit(int *error)
{
    *error = -1;
    return 1;
}
