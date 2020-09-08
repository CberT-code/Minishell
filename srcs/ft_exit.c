/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 16:56:49 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exit(t_cmds *cmd, t_gbl *gbl)
{
	unsigned long long  ret;

	(void)gbl;
	if (cmd->args == NULL)
		return (0);
	if (cmd->args->str)
	{
		if (cmd->args->str[0] == '+' || cmd->args->str[0] == '-')
		{
			ret = ft_atoi_long(cmd->args->str + 1);
			printf("here we test -> %lld\n", ret);
		}
		else
			ret = ft_atoi_long(cmd->args->str);
		if ((!(ft_strisdigit(cmd->args->str + 1))) ||
		(ret > MAXLONG && ft_strcmp(cmd->args->str, "-9223372036854775808") != 0))
			write(2, ARGUMENTS_NUM, ft_strlen(ARGUMENTS_NUM));
	}
	if (cmd->nb_args > 1 || (!ft_strisdigit(cmd->args->str) && (!ft_strisdigit(cmd->args->str + 1) && cmd->args->str[1] != '\0')))
	{
		ret = 2;
		if (ft_strisdigit(cmd->args->str) ||
		(ft_strisdigit(cmd->args->str + 1) &&
		(cmd->args->str[0] == '+' || cmd->args->str[0] == '-')))
			ret = 1;
		write(2, ARGUMENTS, ft_strlen(ARGUMENTS));
		return (ret);
	}
	if (cmd->args->str[0] == '-')
		return ((ret % 256 * -1));
	return (ret % 256);
}
