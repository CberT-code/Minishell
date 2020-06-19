#include "../../minishell.h"

int     ft_echo(char *str, int fd)
{
    int i;
    int ind;

    i = 0;
    ind = 0; 
    if (!str)
        write(1, "\n", 1);
    while (*str == ' ')
        str++;
    if (ft_strncmp(str, "-n", 2) == 0)
    {
        ind = 1;
        str = str + 2;
    }
    while (*str == ' ')
        str++;
    ft_putstr_fd(str, fd);
    if (ind == 0)
        write(1, "\n", 1);
    return (0);
}

// int     main(void)
// {
//     ft_echo("toto", 1);
//     ft_echo("toto echo", 1);
//     ft_echo("toto echo * ", 1);
//     ft_echo("toto echo * dodu", 1);
//     ft_echo("toto echo *c ", 1);
//     ft_echo("toto echo e* ", 1);
//     ft_echo("    -n    tot o1 |", 1);
//     ft_echo("toto -n echo |", 1);
//     ft_echo(" -n toto echo * |", 1);
//     ft_echo("-n toto echo * dodu|", 1);
//     ft_echo("    -n   toto echo *c |", 1);
//     ft_echo("-n toto echo e* |", 1);
//     ft_echo("-ntoto echo e* |", 1);
//     ft_echo("-ntoto echo \"e*\" |", 1);
//     ft_echo("-ntoto echo \"*\" |", 1);

//     ft_echo(" toto '$PWD', 1);
//     ft_echo("toto echo", 1);
//     ft_echo("toto echo * ", 1);
//     ft_echo("toto echo * dodu", 1);
//     ft_echo("toto echo *c ", 1);
//     ft_echo("toto echo e* ", 1);
// }