/*
** EPITECH PROJECT, 2021
** free
** File description:
** free
*/

#include "strace.h"

void free_all(strace tracer)
{
    while (tracer._name_adr != NULL) {
        free(tracer._name_adr->name);
        free(tracer._name_adr);
        tracer._name_adr = tracer._name_adr->next; 
    }
    while (tracer.f_list != NULL) {
        free(tracer.f_list->name);
        free(tracer.f_list);
        tracer.f_list = tracer.f_list->next;
    }
    free(tracer._fileSyscall);
    free(tracer._name_adr);
    free(tracer.f_list);
}
