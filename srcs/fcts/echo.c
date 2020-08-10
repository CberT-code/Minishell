/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:22:56 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/10 12:36:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_echo(t_args *args)
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
