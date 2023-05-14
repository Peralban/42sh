/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include "mysh.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

char *set_term_name(char *name)
{
    static char *term_name = NULL;

    if (name != NULL)
        term_name = strdup(name);
    return term_name;
}

char *get_term_name(void)
{
    return set_term_name(NULL);
}

char *set_color_file(char *color)
{
    static char *color_file = NULL;

    if (color != NULL)
        color_file = strdup(color);
    return color_file;
}

char *get_color_file(void)
{
    return set_color_file(NULL);
}
