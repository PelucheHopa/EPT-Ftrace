/*
** EPITECH PROJECT, 2020
** memory_ftrace
** File description:
** memory_ftrace
*/

#include "../include/memory_ftrace.h"
#include "../include/strace.h"

memory_ftrace_t *add_in_memory(memory_ftrace_t *stack, char *_name, int _adress)
{
    memory_ftrace_t *new = malloc(sizeof(memory_ftrace_t));
    memory_ftrace_t *current = stack;

    new->name = _name;
    new->adress = _adress;
    new->next = NULL;
    if (stack == NULL) current = new;
    else {
        while (current->next != NULL) current = current->next;
        current->next = new;
    }
    return (current);
}

memory_ftrace_t *pop_memory(memory_ftrace_t *stack)
{
    memory_ftrace_t *to_pop = stack;
    memory_ftrace_t *prev;

    if (stack == NULL) return (NULL);
    if (to_pop->next == NULL) {
        stack = NULL;
        return (to_pop);
    }
    while (to_pop->next != NULL) {
        prev = to_pop;
        to_pop = to_pop->next;
    }
    prev->next = NULL;
    return (prev);
}
