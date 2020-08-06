/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:22:56 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/06 08:39:30 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     ft_echo(t_args *args)
{
    int flag;

    flag = 0;
    if (!args || !(args)->str)
    {
        write(1, "\n", 1);
        return (0);
    }
    while (args)
    {
        if (ft_strlen((args)->str) == 2 && (args)->str[0] == '-'
        && (args)->str[1] == 'n')
            flag = 1;
        else
        {
            ft_printf("%s", (args)->str);
            if ((args)->next != NULL)
                ft_printf(" ");
        }
        (args) = (args)->next;
    }
    if (flag == 0)
        ft_printf("\n");
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