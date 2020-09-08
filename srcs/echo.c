/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:22:56 by cbertola          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/09/06 21:09:42 by cbertola         ###   ########.fr       */
=======
/*   Updated: 2020/09/07 18:44:48 by user42           ###   ########.fr       */
>>>>>>> mike
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_echo(t_args *args, t_gbl *gbl)
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
			args->str = ft_replace_value(args->str, gbl);
			ft_printf("%s", (args)->str);
			if ((args)->next != NULL)
				ft_printf(" ");
		}
		(args) = (args)->next;
	}
	if (flag == 0)
		ft_printf("\n");
	return (gbl->ret = 0);
}
