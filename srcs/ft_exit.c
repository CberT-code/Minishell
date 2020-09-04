/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 17:14:17 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_exit(t_cmds *cmd, t_gbl *gbl)
{
    int i;

    i = 0;
    if (cmd->args->str)
    {
        if (cmd->args->str[i] == '+' || cmd->args->str[i] == '-')
            i++;
        if ((!(ft_strisdigit(cmd->args->str + i))) ||
        ft_atoi_long(cmd->args->str) > 2147483647 ||
        ft_atoi_long(cmd->args->str) < -2147483648)
        {
            free_exit2(gbl, ARGUMENTS_NUM);
            return (0);
        }
    }
    if (cmd->nb_args > 1)
    {
        free_exit2(gbl, ARGUMENTS);
        return (0);
    }
    return (1);
}