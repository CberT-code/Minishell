/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 23:03:00 by user42            #+#    #+#             */
/*   Updated: 2020/08/29 22:26:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_cd_errors(t_env *env)
{
	if (chdir(ft_getenv("HOME=", env)) != 0)
	{
		ft_putendl("bash: cd: « HOME » non défini");
		g_ret = 1;
		return (1);
	}
	g_ret = 0;
	return (0);
}

int		ft_check_size_args_cd(t_args *args)
{
	if (ft_size_args(args) > 1)
	{
		ft_putendl("bash: cd: trop d'arguments");
		g_ret = 1;
		return (1);
	}
	g_ret = 0;
	return (0);
}
