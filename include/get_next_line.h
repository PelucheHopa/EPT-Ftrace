/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#define GET_H_
#ifdef GET_H_

#define READ_SIZE 42

struct s_str
{
    char *after;
    int lock;
    int valid;
    int block;
};

struct s_int
{
    char *buff;
    int a;
    int b;
};

char *get_next_line(int fd);

#endif
