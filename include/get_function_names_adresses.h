/*
** EPITECH PROJECT, 2019
** get_function_names_adresses
** File description:
** get_function_names_adresses
*/

#define GET_FUNCTION_NAMES_ADRESSES_H_
#ifdef GET_FUNCTION_NAMES_ADRESSES_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>
#include <unistd.h>
#include <stdlib.h>
#include <elf.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct name_adresses_s {
    char *name;
    unsigned value;
    int size;
    Elf64_Addr adress;
    Elf64_Ehdr elf_addr;
    struct name_adresses_s *next;
} name_adresses_t;

Elf64_Ehdr get_start(char *filename);

name_adresses_t *get_names_adresses(char *filename);

char *get_name_by_adress(name_adresses_t *names_adresses, int adress);
//char *get_name_by_adress(name_adresses_t *names_adresses, Elf64_Addr adress);
//char *get_name_by_adress(name_adresses_t *names_adresses, int base_address, int opcode, int rip);

#endif
