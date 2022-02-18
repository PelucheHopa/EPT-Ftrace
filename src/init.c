/*
** EPITECH PROJECT, 2021
** init
** File description:
** init
*/

#include "strace.h"
#include "get_next_line.h"

file_syscall take_name(file_syscall _fileSyscall)
{
    int x = 0;
    int n = 0;
    char *nbr_args = malloc(sizeof(char) * 2);

    for (; _fileSyscall.command[x] != ' '; x++);
    for (x++; _fileSyscall.command[x] != ' '; x++);
    for (x++; _fileSyscall.command[x] != ' '; x++, n++);
    _fileSyscall.name = malloc(sizeof(char) * n + 1);
    x = x - n;
    for (n = 0; _fileSyscall.command[x] != ' '; x++, n++) {
        _fileSyscall.name[n] = _fileSyscall.command[x];
        _fileSyscall.name[n + 1] = '\0';
    }
    for (x++; _fileSyscall.command[x] != ' '; x++, n++);
    x++;
    nbr_args[0] = _fileSyscall.command[x];
    nbr_args[1] = '\0';
    _fileSyscall.nbr_args = atoi(nbr_args);
    return (_fileSyscall);
}

file_syscall *init_fileSyscall(file_syscall *_fileSyscall)
{
    int fd = open("src/syscall.txt", O_RDONLY);
    char *map = NULL;

    if (fd == -1) exit(84);
    _fileSyscall = malloc(sizeof(file_syscall) * 443);
    for (int letter = 0; letter < 443; letter++) {
        _fileSyscall[letter].command = get_next_line(fd);
        _fileSyscall[letter + 1].command = NULL;
    }
    for (int x = 0; _fileSyscall[x].command != NULL; x++)
        _fileSyscall[x] = take_name(_fileSyscall[x]);
    close(fd);
    get_next_line(-42);
    return (_fileSyscall);
}

strace init_struct_strace(strace tracer, char *file)
{
    tracer._pid = 0;
    tracer.status = 0;
    tracer.compt = 0;
    tracer._s_option = NOTAVAILABLE;
    tracer._fileSyscall = init_fileSyscall(tracer._fileSyscall);
    tracer._name_adr = get_names_adresses(file);
    tracer.f_list = NULL;
    tracer._pid = fork();
    tracer.file = file;
    return (tracer);
}
