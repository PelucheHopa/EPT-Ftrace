/*
** EPITECH PROJECT, 2019
** get_function_names_adresses
** File description:
** get_function_names_adresses
*/

#include "get_function_names_adresses.h"

name_adresses_t *init_tab(Elf_Data *data, Elf *elf, GElf_Shdr shdr)
{
    name_adresses_t *first;
    GElf_Sym sym;

    if (shdr.sh_size / shdr.sh_entsize >= 1) {
        gelf_getsym(data, 1, &sym);
        first = malloc(sizeof(name_adresses_t));
        first->name = elf_strptr(elf, shdr.sh_link, sym.st_name);
        first->adress = sym.st_value;
        first->next = NULL;
        return (first);
    } else
        return (NULL);
}


Elf64_Ehdr get_start(char *filename)
{
    FILE* fp = NULL; //Pointer used to access current file
    Elf64_Ehdr elf_header; //Elf header
    Elf64_Shdr* sh_table; //Elf symbol table

    fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_SET);
    fread(&elf_header, 1, sizeof(Elf64_Ehdr), fp);
    return (elf_header);
}

name_adresses_t *make_tab(Elf_Data *data, Elf *elf, GElf_Shdr shdr)
{
    GElf_Sym sym;
    char *name;
    int adress;

    name_adresses_t *first = init_tab(data, elf, shdr);
    name_adresses_t *current;
    name_adresses_t *prev;

    prev = first;
    for (int i = 1; i < shdr.sh_size / shdr.sh_entsize; ++i) {
        gelf_getsym(data, i, &sym);
        current = malloc(sizeof(name_adresses_t));
        current->name = elf_strptr(elf, shdr.sh_link, sym.st_name);
        current->value = sym.st_value;
        current->size = sym.st_size;
        current->next = NULL;
        prev->next = current;
        prev = prev->next;
    }
    return (first);
}

name_adresses_t *get_names_adresses(char *filename)
{
    Elf *elf;
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    Elf_Data *data;
    int fd = open(filename, O_RDONLY);
    name_adresses_t *res;

    elf_version(EV_CURRENT);
    elf = elf_begin(fd, ELF_C_READ, NULL);
    while((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_SYMTAB) {
            break;
        }
    }
    data = elf_getdata(scn, NULL);
    res = make_tab(data, elf, shdr);
    elf_end(elf);
    close(fd);
    res->elf_addr = get_start(filename);

    name_adresses_t *current = res;

    return (res);
}

char *get_name_by_adress(name_adresses_t *names_adresses, int adress)
{
    name_adresses_t *current = names_adresses;

    while (current != NULL) {
        if (current->value == adress)
            return (current->name);
        current = current->next;
    }
    return (NULL);
}

long get_adress_of_elf_file(char *filename)
{
    void *data;
    struct stat stat;
    int fd;

    if (lstat(filename, &stat) == -1) {
        printf("'%s': no such file\n", filename);
        return (0);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("error during the opening of the file");
        return (0);
    }
    data = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED)
        return (0);
    return ((long) data);
}
