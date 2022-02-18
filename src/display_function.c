/*
** EPITECH PROJECT, 2021
** ptrace
** File description:
** ptrace
*/


#include "strace.h"
#include "get_next_line.h"

void ftrace_entering(strace *tracer)
{
    char *str = get_name_by_adress(tracer->_name_adr, tracer->_regs.rip);

    if (str != NULL) {
        if (str[0] > 33 && str[0] < 127 && str[0] != '@' ) {
            printf("Entering function %s at 0x%lx\n", str, tracer->_regs.rip);
        }
        else
            printf("Entering function ??? at %x@%s\n", tracer->_regs.rip, tracer->file);
        tracer->f_list = add_in_memory(tracer->f_list, str, tracer->_regs.rip);
        tracer->compt++;
    }
}

void ftrace_leaving(strace *tracer)
{
    memory_ftrace_t *tmp = tracer->f_list;

    while (tmp->next != NULL) tmp = tmp->next;
    if (tmp->name[0] > 33 && tmp->name[0] < 127 && tmp->name[0] != '@')
        printf("Leaving function %s\n", tmp->name);
    else
        printf("Leaving function ??? at %x@%s\n", tracer->f_list->adress, tracer->file);
    tracer->f_list = pop_memory(tracer->f_list);
    tracer->compt--;
}
