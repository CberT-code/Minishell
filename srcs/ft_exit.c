/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 22:33:12 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exit(t_cmds *cmd, t_gbl *gbl)
{
	unsigned long long	ret;
	int					i;

	i = 0;
	if (cmd->args == NULL)
		return (0);
	if (cmd->args->str)
	{
		if (cmd->args->str[i] == '+' || cmd->args->str[i] == '-')
			i++;
		ret = ft_atoi_long(cmd->args->str + i);
		if (!(ft_strisdigit(cmd->args->str + i)) || (ret > MAXLONG &&
		ft_strcmp(cmd->args->str, "-9223372036854775808") != 0))
			free_exit_int(gbl->semi, gbl, ARGUMENTS_NUM, 2);
		else if (cmd->nb_args > 1)
			free_exit_int(gbl->semi, gbl, ARGUMENTS, 1);
		else if (cmd->args->str[0] == '-')
			return ((ret % 256 * -1));
		else
			return (ret % 256);
	}
	return (0);
}
