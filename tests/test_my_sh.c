/*
** EPITECH PROJECT, 2023
** criterion tests for 42sh
** File description:
** tests
*/
#include <criterion/criterion.h>
#include "criterion/assert.h"
#include "criterion/redirect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Test(my_sh, test_echo_hello_world) {
    char* command = "echo Hello\n";
    FILE* pipe = popen("./42sh", "w");
    char output[100];

    fprintf(pipe, "%s", command);
    pclose(pipe);
    pipe = popen("cat .output", "r");
    fgets(output, 100, pipe);
    cr_assert_str_eq(output, "Hello\n");
    pclose(pipe);
}
