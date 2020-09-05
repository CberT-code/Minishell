/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 14:42:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_exit(t_cmds *cmd, t_gbl *gbl)
{
    int i;

    i = 0;
    if (cmd->args == NULL)
        return (1);
    if (cmd->args->str)
    {
        if (cmd->args->str[i] == '+' || cmd->args->str[i] == '-')
            i++;
        if ((!(ft_strisdigit(cmd->args->str + i))) ||
        ft_atoi_long(cmd->args->str) > 9223372036854775807 ||
        ft_atoi_long(cmd->args->str) < -9223372036854775807)
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