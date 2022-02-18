/*
** EPITECH PROJECT, 2021
** error
** File description:
** error
*/

#include "strace.h"
#include "get_next_line.h"

void error_check(int ac, char **av)
{
    if (ac != 2) exit (84);
    if (strcmp(av[1], "--help") == 0) usage();
}

void error_signal(int status, strace tracer)
{
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        exit(0);
    }
}
