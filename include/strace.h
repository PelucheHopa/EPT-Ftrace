/*
** EPITECH PROJECT, 2021
** strace
** File description:
** strace
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_function_names_adresses.h"
#include "memory_ftrace.h"

#define IS_RET(x) ((x & 0x3800) == 0x1000 ? 1 : 0)

typedef struct s_syscall
{
    char *name;
    char *command;
    int nbr_args;
} file_syscall;

typedef enum s_option
{
    AVAILABLE,
    NOTAVAILABLE
} s_option;

typedef struct s_strace {
    int status;
    int compt;
    int _base_address;
    char *file;
    pid_t _pid;
    s_option _s_option;
    file_syscall *_fileSyscall;
    name_adresses_t *_name_adr;
    memory_ftrace_t *f_list;
    struct user_regs_struct _regs;
} strace;

char *getstr(int nbr);

char *create_path(char *pid);

int init_base_address(char *pid);

file_syscall *init_fileSyscall(file_syscall *_fileSyscall);

strace init_struct_strace(strace tracer, char *file);

strace turn_off(strace trace);

void display_syscall_arg(file_syscall _fileSyscall, struct user_regs_struct _regs);

void usage();

void error_check(int ac, char **av);

void error_signal(int status, strace tracer);

void ftrace_entering(strace *tracer);

void ftrace_leaving(strace *tracer);

void free_all(strace tracer);

#endif
