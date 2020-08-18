/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/08/15 10:44:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(t_args *args)
{
	char	cwd[1024];

	if (!args)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			ft_putendl(cwd);
			return (0);
		}
		ft_putstr("pwd : Error - Failed to get pwd\n");
		return (1);
	}
	ft_putstr("pwd : Too many arguments\n");
	return (1);
}
