/*
** EPITECH PROJECT, 2019
** get
** File description:
** get
*/

#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

struct s_str save_reader(struct s_str str, struct s_int var, char *stock)
{
    if (var.buff[var.b] == '\0' && var.b < READ_SIZE) {
        for (; str.after[var.a] >= 1 && str.after[var.a] <= 126
                 && str.lock == 0 && str.after[var.a] != '\0'; var.a++);
        str.after[var.a] = '\0';
        str.lock = 1;
        str.block = 1;
        return (str);
    }
    for (var.a = 0; stock[var.a] != '\0'; var.a++);
    for (; var.buff[var.b] != '\0'; var.a++, var.b++)
        stock[var.a] = var.buff[var.b];
    return (str);
}

struct s_str inp_read(struct s_str str, struct s_int var, int fd, char *stock)
{
    fd = read(fd, var.buff, READ_SIZE);
    while (var.buff[var.b] != '\n' && var.buff[var.b] != '\0') {
        str.after[var.a] = var.buff[var.b];
        var.a++;
        var.b++;
    }
    if (var.buff[var.b + 1] == '\0' && var.b + 1 < READ_SIZE) {
        str.block = 2;
        str.lock = 1;
        return (str);
    }
    if (var.buff[var.b] == '\n') {
        str.after[var.a] = '\0';
        str.lock = 1;
        var.b++;
        var.a++;
    }
    return (save_reader(str, var, stock));
}

struct s_str input_stock(struct s_str str, char *stock, int a, int b)
{
    for (; stock[b] != '\0' && stock[b] != '\n'; a++, b++) {
        str.after[a] = stock[b];
        stock[b] = '\0';
    }
    if (stock[b] == '\n') {
        str.after[a] = '\0';
        stock[b] = '\0';
        a++;
        b++;
        str.lock = 1;
    }
    for (int over = 0; stock[b] != '\0'; b++, over++) {
        stock[over] = stock[b];
        stock[b] = '\0';
    }
    return (str);
}

struct s_str read_function(struct s_str str, int fd)
{
    static char stock[1000 * READ_SIZE];
    struct s_int var;

    var.a = 0;
    var.b = 0;
    var.buff = malloc(sizeof(char) * (1000 * READ_SIZE));
    for (; str.after[var.a] != '\0'; var.a++);
    str = input_stock(str, stock, var.a, var.b);
    for (var.a = 0; str.after[var.a] != '\0'; var.a++);
    if (str.lock == 1)
        return (str);
    return (inp_read(str, var, fd, stock));
}

char *get_next_line(int fd)
{
    struct s_str str;
    static int null = 0;

    if (fd == -42) null = 0;
    if (fd < 0) {
        return (NULL);
    }
    if (READ_SIZE == 0 || READ_SIZE < 0) {
        return (NULL);
    }
    str.after = malloc(sizeof(char) * (1000 * READ_SIZE));
    for (str.lock = 0, str.block = 0; str.lock == 0;) {
        if (null == 1) {
            return (NULL);
        }
        str = read_function(str, fd);
        if (str.block == 1 || str.block == 2)
            null = 1;
        if (str.block == 2 && str.after[0] == '\0') {
            return (NULL);
        }
    }
    return (str.after);
}
