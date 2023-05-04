/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

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
