/*
** EPITECH PROJECT, 2023
** my_put_errors.c
** File description:
** functions that print error on function execution
*/

#include "my.h"
#include "command_error_handling.h"

void my_put_permission_denied(char *cmd)
{
    my_putstr(cmd);
    my_putstr(": Permission denied.\n");
}

void my_put_command_not_found(char *cmd)
{
    my_putstr(cmd);
    my_putstr(": Command not found.\n");
}
