/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/07 21:52:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exit(t_cmds *cmd, t_gbl *gbl)
{
	int i;
	int ret;
	int ret2;

	i = 0;
	if (cmd->args == NULL)
		return (1);
	if (cmd->args->str)
	{
		if (cmd->args->str[i] == '+' || cmd->args->str[i] == '-')
			i++;
		if ((!(ft_strisdigit(cmd->args->str + i))) || (cmd->args->str[0] == '+'
		&& (ret = ft_atoi_long(cmd->args->str + 1) > MAXLONG)) ||
		(cmd->args->str[0] == '-' && ft_atoi_long(cmd->args->str + 1) > MAXLONG
		&& ft_strcmp(cmd->args->str, "-9223372036854775808") != 0) ||
		(ret2 = ft_atoi_long(cmd->args->str) > MAXLONG))
		{
			free_exit2(gbl, ARGUMENTS_NUM);
			return (0);
		}
	}
	if (cmd->nb_args > 1)
	{
		free_exit2(gbl, ARGUMENTS);
		return (1);
	}
	return (ret2);
}
