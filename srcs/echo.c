/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:22:56 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 15:10:47 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			(args)->str = ft_replace_value((args)->str);
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
