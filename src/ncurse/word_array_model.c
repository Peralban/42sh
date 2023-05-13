/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

#include <stdlib.h>
#include "../include/my_getline.h"
#include "../include/my.h"
#include "../include/mysh.h"

static void get_word_model(char **str, char *delim, char ***arr, int *swa)
{
    char *model = str[0];
    char *src = str[1];

    if (isin(model[swa[SWA_I] - 1], delim) &&
    !(isin(model[swa[SWA_I]], delim))) {
        swa[SWA_BEGIN] = swa[SWA_I];
        swa[SWA_K] = -1;
    } if (!(isin(model[swa[SWA_I] - 1], delim)) &&
    isin(model[swa[SWA_I]], delim)) {
        add_to_arr(arr, src, swa);
    } if (swa[SWA_K] >= swa[SWA_MAX] - 2 &&
    !isin(model[swa[SWA_I] - 1], delim) &&
    !isin(model[swa[SWA_I]], delim)) {
        add_to_arr(arr, src, swa);
        swa[SWA_K] -= 1;
        swa[SWA_BEGIN] = swa[SWA_I] + 1;
        if (isin(model[swa[SWA_I] + 1], delim))
            swa[SWA_I]++;
    }
}

// take a model and apply the str_to_word_array_max_size function on a src
// based on the modification that the model would receive
char **my_str_to_word_array_max_size_model(char *model, char *delim,
int max_size, char *src)
{
    int *swa = malloc(sizeof(int) * (SWA_MAX + 1));
    char **arr = malloc(sizeof(char*));
    char **str = malloc(sizeof(char*) * 2);

    str[0] = model;
    str[1] = src;
    if (src == NULL || arr == NULL || swa == NULL ||
        model == NULL || str == NULL)
        return NULL;
    init_swa(max_size, swa);
    arr[0] = NULL;
    for (; model[swa[SWA_I]] != 0; swa[SWA_I]++, swa[SWA_K]++) {
        get_word_model(str, delim, &arr, swa);
        if (arr == NULL)
            return NULL;
    }
    if (!(isin(model[swa[SWA_I] - 1], delim)))
        add_to_arr(&arr, src, swa);
    free(swa);
    return arr;
}
