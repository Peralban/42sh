/*
** EPITECH PROJECT, 2023
** command_error_handling.h
** File description:
** command_error_handling
*/

#pragma once

typedef enum is_existing_e {
    NOT_EXISTING,
    ACCESSIBLE,
    NOT_ACCESSIBLE,
    ERROR
} is_existing_t;

char *search_command(char *cmd, char **env, int *error);
void my_put_permission_denied(char *cmd);
void my_put_command_not_found(char *cmd);
