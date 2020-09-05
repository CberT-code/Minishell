/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 18:14:57 by cbertola         ###   ########.fr       */
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
        if ((!(ft_strisdigit(cmd->args->str + i))) || (cmd->args->str[0] == '+' 
        && ft_atoi_long(cmd->args->str + 1) > 9223372036854775807) ||
        (cmd->args->str[0] == '-' 
        && ft_atoi_long(cmd->args->str + 1) > 9223372036854775807 &&
        ft_strcmp(cmd->args->str, "-9223372036854775808") != 0) ||
        ft_atoi_long(cmd->args->str) > 9223372036854775807)
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