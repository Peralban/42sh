/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>
#include "../include/my_getline.h"
#include "../include/my.h"

char *my_strdupij_endin(const char *str, int begin, int end)
{
    char *new_str = malloc(sizeof(char) * (end - begin + 2));
    int j = 0;

    if (new_str == NULL)
        return NULL;
    for (int i = begin; i <= end; i++, j++)
        new_str[j] = str[i];
    new_str[j] = '\0';
    return new_str;
}

void add_to_arr(char ***arr, char *str, int *swa)
{
    swa[SWA_END] = swa[SWA_I];
    (*arr) = realloc(*arr, sizeof(char*) * (swa[SWA_N] + 2));
    if (*arr == NULL)
        return;
    (*arr)[swa[SWA_N]] = my_strdupij_endin(str, swa[SWA_BEGIN], swa[SWA_END]);
    (*arr)[swa[SWA_N] + 1] = NULL;
    swa[SWA_N]++;
    swa[SWA_K] = -1;
}

void get_word(char *str, char *delim, char ***arr, int *swa)
{
    if (isin(str[swa[SWA_I] - 1], delim) && !(isin(str[swa[SWA_I]], delim))) {
        swa[SWA_BEGIN] = swa[SWA_I];
        swa[SWA_K] = -1;
    }
    if (!(isin(str[swa[SWA_I] - 1], delim)) && isin(str[swa[SWA_I]], delim)) {
        add_to_arr(arr, str, swa);
    }
    if (swa[SWA_K] >= swa[SWA_MAX] - 2 && !isin(str[swa[SWA_I] - 1], delim) &&
    !isin(str[swa[SWA_I]], delim)) {
        add_to_arr(arr, str, swa);
        swa[SWA_K]--;
        swa[SWA_BEGIN] = swa[SWA_I] + 1;
        if (isin(str[swa[SWA_I] + 1], delim))
            swa[SWA_I]++;
    }
}

char **my_str_to_word_array_max_size(char *str, char *delim, int max_size)
{
    int *swa = malloc(sizeof(int) * (SWA_MAX));
    char **arr = malloc(sizeof(char*));
    if (str == NULL || arr == NULL || swa == NULL)
        return NULL;
    swa[SWA_MAX] = max_size;
    swa[SWA_I] = 1;
    swa[SWA_N] = 0;
    swa[SWA_K] = 0;
    swa[SWA_BEGIN] = 0;
    swa[SWA_END] = 0;
    arr[0] = NULL;
    for (; str[swa[SWA_I]] != 0; swa[SWA_I]++, swa[SWA_K]++) {
        get_word(str, delim, &arr, swa);
        if (arr == NULL)
            return NULL;
    }
    if (!(isin(str[swa[SWA_I] - 1], delim))) {
        add_to_arr(&arr, str, swa);
    }
    return arr;
}
