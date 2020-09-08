/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:50:14 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 20:49:39 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isbracket(char *str, int i)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == '}')
		return (1);
	return (0);
}

int		ft_travel_brackets(char *str, int i, t_gbl *gbl)
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
			free_exit2(gbl, "Accolade manquante");
			return (0);
		}
		if (str[i] == '}' && str[i - 1] == '{')
		{
			free_exit2(gbl, "Mauvaise substitution");
			return (0);
		}
	}
	return (1);
}

int		ft_verif_doubq(char *str, int *i, t_gbl *gbl)
{
	int ret;

	ret = 1;
	if (str[*i] == DOUBQ && ft_isbacks(str, (*i) - 1) == 0)
	{
		(*i)++;
		while (ft_isquote(str, *i) != 2 && str[*i])
		{
			if ((ret = ft_travel_brackets(str, *i, gbl)) != 1)
					return (0);
			(*i)++;
		}
		if (str[(*i)] != DOUBQ)
		{
			free_exit2(gbl, "Double quote manquante");
			return (0);
		}
	}
	return (1);
}

int		ft_verif_simpq(char *str, int *i, t_gbl *gbl)
{
	if (str[*i] == SIMPQ && ft_isbacks(str, (*i) - 1) == 0)
	{
		(*i)++;
		while (ft_isquote(str, *i) != 2 && str[*i])
			(*i)++;
		if (str[(*i) - 1] != SIMPQ)
		{
			free_exit2(gbl, "Simple quote manquante");
			return (0);
		}
	}
	return (1);
}

int		ft_verif_commands(char *str, t_gbl *gbl)
{
	int i;
	int ret;

	i = -1;
	ret = 1;
	while (str[++i])
	{
		if (ft_verif_doubq(str, &i, gbl) == 0
		|| ft_verif_simpq(str, &i, gbl) == 0)
			return (0);
		if ((ret = ft_travel_brackets(str, i, gbl)) != 1)
			return (0);
	}
	return (1);
}
