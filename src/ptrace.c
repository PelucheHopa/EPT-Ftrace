/*
** EPITECH PROJECT, 2021
** ptrace
** File description:
** ptrace
*/


#include "strace.h"
#include "get_next_line.h"

void exec(char **av)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl(av[1], "", NULL);
}

void kind_call(strace *tracer, short opcode)
{
    if ((opcode & 0xffff) == 0x050f)
        display_syscall_arg(tracer->_fileSyscall[tracer->_regs.rax], tracer->_regs);
    else ftrace_entering(tracer);
    if (IS_RET(opcode) && tracer->compt > 0) ftrace_leaving(tracer);
}

void trace(strace tr)
{
    short opcode;
    siginfo_t signal;

    waitpid(tr._pid, &tr.status, 0);
    tr._base_address = init_base_address(getstr(tr._pid));
    for (;;) {
        ptrace(PTRACE_GETREGS, tr._pid, NULL, &tr._regs);
        opcode = ptrace(PTRACE_PEEKTEXT, tr._pid, (void *)tr._regs.rip, NULL);
        ptrace(PTRACE_GETSIGINFO, tr._pid, NULL, &signal);
        kind_call(&tr, opcode);
        ptrace(PTRACE_SINGLESTEP, tr._pid, NULL, NULL);
        waitpid(tr._pid, &tr.status, 0);
        error_signal(tr.status, tr);
    }
}

void ftrace(int ac, char **av)
{
    strace tracer;

    tracer = init_struct_strace(tracer, av[1]);
    if (tracer._pid == 0) exec(av);
    else trace(tracer);
}

int main(int ac, char **av)
{
    int rtn = 0;

    error_check(ac, av);
    ftrace(ac, av);
}
