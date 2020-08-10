/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 13:48:24 by user42            #+#    #+#             */
/*   Updated: 2020/08/10 12:28:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		in_quotes(char *s, int i, int in)
{
	int	j;

	j = 0;
	in = 0;
	while (j <= i)
	{
		if (s[j] == '\'' || s[j] == '\"')
			in = in == 0 ? 1 : 0;
		j++;
	}
	return (in);
}

int		ft_in_quotes(char *str, int i)
{
	int	quote;
	int	dbquote;
	int	j;
	int	last;

	quote = 0;
	dbquote = 0;
	last = 0;
	j = -1;
	while (++j < i)
	{
		if ((j > 0 && str[j] == SIMPQ && ft_isbacks(str, j - 1) == 0)
				|| (j == 0 && str[j] == SIMPQ))
		{
			quote++;
			last = 1;
		}
		if ((j > 0 && str[j] == DOUBQ && ft_isbacks(str, j - 1) == 0)
				|| (j == 0 && str[j] == DOUBQ))
		{
			dbquote++;
			last = 2;
		}
	}
	if (quote % 2 != 0 || dbquote % 2 != 0)
		return (last);
	return (0);
}

int		ft_isbacks(char *str, int i)
{
	int	cpt;

	cpt = 0;
	while (i >= 0 && str[i] == BACKS)
	{
		cpt++;
		i--;
	}
	if (cpt % 2 == 0)
		return (0);
	return (1);
}

int		ft_isquote(char *str, int i)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == DOUBQ)
		return (2);
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == SIMPQ)
		return (1);
	return (0);
}
