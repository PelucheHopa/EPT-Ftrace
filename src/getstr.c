/*
** EPITECH PROJECT, 2021
** getst
** File description:
** getstr
*/

#include <unistd.h>
#include <stdlib.h>

char *getstr(int nbr)
{
    char *str = NULL;
    char *rstr = NULL;
    int mult = 1;
    int a = 0;

    for (; nbr / mult > 1; mult = mult * 10, a++);
    str = malloc(sizeof(char) * (a + 1));
    rstr = malloc(sizeof(char) * (a + 1));
    for (a = 0; nbr >= 1; nbr = nbr / 10, a++) {
        str[a] = nbr % 10 + 48;
        str[a + 1] = '\0';
    }
    a--;
    for (int b = 0; a >= 0; a--, b++) {
        rstr[b] = str[a];
        rstr[b + 1] = '\0';
    }
    return (rstr);
}
