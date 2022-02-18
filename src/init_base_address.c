/*
** EPITECH PROJECT, 2021
** init
** File description:
** init
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char *create_path(char *pid)
{
    char proc[] = "/proc/";
    char maps[] = "/maps";
    char *path = NULL;
    int a = 0;

    for (; proc[a] != '\0'; a++);
    path = malloc(sizeof(char) * (11 + a));
    a = 0;
    for (int b = 0; proc[b] != '\0'; a++, b++) path[a] = proc[b];
    for (int b = 0; pid[b] != '\0'; a++, b++) path[a] = pid[b];
    for (int b = 0; maps[b] != '\0'; a++, b++) path[a] = maps[b];
    path[a] = '\0';
    return (path);
}

int init_base_address(char *pid)
{
    int fd = open(create_path(pid), O_RDONLY);
    char *address = get_next_line(fd);

    get_next_line(-42);
    close(fd);
    return (atoi(address));
}
