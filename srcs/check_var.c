/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:59:44 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/15 10:40:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_str_alpha(char *str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int		check_str_digitspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < 48 || str[i] > 57) && str[i] != 32)
			return (0);
	}
	return (1);
}

void	check_line(char *str)
{
	if (ft_strncmp(str, "exit", 4) == 0
	&& (*(str + 4) == ' ' || *(str + 4) == '\0'))
		if (check_str_digitspace(str + 4) == 1 || *(str + 4) == '\0')
			exit(ft_atoi(str + 4));
}
