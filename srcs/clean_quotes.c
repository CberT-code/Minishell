/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:50:14 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/07 13:39:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isbracket(char *str, int i)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == '}')
		return (1);
	return (0);
}

int		ft_travel_brackets(char *str, int i)
{
	int dollar;

	dollar = 0;
	if (str[i] == '{')
	{
		if (i > 0 && str[i - 1] == '$' && ft_isbacks(str, i - 2) == 0)
			dollar = 1;
		i++;
		while (ft_isbracket(str, i) != 1 && str[i])
			i++;
		if (str[i] != '}' && dollar == 1)
		{
			ft_putstr_fd("Accolade manquante", 2);
			return (0);
		}
	}
	return (1);
}

int		ft_verif_doubq(char *str, int *i)
{
	int ret;

	ret = 1;
	if (str[*i] == DOUBQ && ft_isbacks(str, (*i) - 1) == 0)
	{
		(*i)++;
		while (ft_isquote(str, *i) != 2 && str[*i])
		{
			if ((ret = ft_travel_brackets(str, *i)) != 1)
					return (0);
			(*i)++;
		}
		if (str[(*i)] != DOUBQ)
		{
			ft_putstr_fd("Double quote manquante", 2);
			return (0);
		}
	}
	return (1);
}

int		ft_verif_simpq(char *str, int *i)
{
	if (str[*i] == SIMPQ && ft_isbacks(str, (*i) - 1) == 0)
	{
		(*i)++;
		while (ft_isquote(str, *i) != 2 && str[*i])
			(*i)++;
		if (str[(*i) - 1] != SIMPQ)
		{
			ft_putstr_fd("Simple quote manquante", 2);
			return (0);
		}
	}
	return (1);
}

int		ft_verif_commands(char *str)
{
	int i;
	int ret;

	i = -1;
	ret = 1;
	while (str[++i])
	{
		if (ft_verif_doubq(str, &i) == 0
		|| ft_verif_simpq(str, &i) == 0)
			return (0);
		if ((ret = ft_travel_brackets(str, i)) != 1)
			return (0);
	}
	return (1);
}
