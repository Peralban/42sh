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

char *create_term_name(void)
{
    char *term_name = NULL;
    char *file = ".42sh_term";
    char *home = gethome(my_getpwd());

    term_name = malloc(sizeof(char) * (strlen(home) + strlen(file) + 2));
    if (term_name == NULL)
        return NULL;
    term_name[0] = '\0';
    strcat(term_name, home);
    strcat(term_name, "/");
    strcat(term_name, file);
    return term_name;
}
