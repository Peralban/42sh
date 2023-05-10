/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

char **set_env_tab(char **new_env)
{
    static char **env = NULL;

    if (new_env != NULL)
        env = new_env;
    return env;
}

char **get_env_tab(void)
{
    return set_env_tab(NULL);
}
