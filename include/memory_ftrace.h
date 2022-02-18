/*
** EPITECH PROJECT, 2020
** ftrace
** File description:
** ftrace
*/

#ifndef MEMORY_FTRACE_H
#define MEMORY_FTRACE_H

typedef struct s_memory_ftrace {
    char *name;
    int adress;
    struct s_memory_ftrace *next;
} memory_ftrace_t;

memory_ftrace_t *add_in_memory(memory_ftrace_t *stack, char *_name, int _adress);

memory_ftrace_t *pop_memory(memory_ftrace_t *stack);

#endif
