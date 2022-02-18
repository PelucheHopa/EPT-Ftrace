/*
** EPITECH PROJECT, 2021
** syscall
** File description:
** syscall
*/

#include "get_next_line.h"
#include "strace.h"

strace turn_off(strace trace)
{
    trace._regs.rdi = 0;
    trace._regs.rsi = 0;
    trace._regs.rdx = 0;
    trace._regs.rcx = 0;
    return (trace);
}

void display_syscall_arg(file_syscall _fileSyscall, struct user_regs_struct _regs)
{
    printf("Syscall %s", _fileSyscall.name);
    if (_fileSyscall.nbr_args > 0) printf("(0x%x", _regs.rdi);
    if (_fileSyscall.nbr_args > 1) printf(", 0x%x", _regs.rsi);
    if (_fileSyscall.nbr_args > 2) printf(", 0x%x", _regs.rdx);
    if (_fileSyscall.nbr_args > 3) printf(", 0x%x", _regs.rcx);
    if (_fileSyscall.nbr_args > 4) printf(", 0x%x", _regs.r8);
    if (_fileSyscall.nbr_args > 5) printf(", 0x%x", _regs.r9);
    if (_fileSyscall.nbr_args > 0) printf(")");
    printf(" = 0x%llx\n", _regs.rax);
}
