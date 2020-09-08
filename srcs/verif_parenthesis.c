/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:50:14 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 11:03:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isparanthesis(char *str, int i)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == ')')
		return (1);
	return (0);
}

int		ft_travel_paranthesis(char *str)
{
	int i;

	i = 1;
	while (ft_isparanthesis(str, i) != 1 && str[i])
		i++;
	if (str[i] != ')')
	{
		ft_putstr_fd("Paranthèse manquante.", 2);
		return (-1);
	}
	return (i);
}

int		ft_verif_paranthesis(char *str)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	while (str[++i])
	{
		ft_travel_simpq(str, &i);
		if (i >  0 && str[i] == '('
		&& str[i -1] == '$' && ft_isbacks(str, i - 2) == 0)
			ret = ft_travel_paranthesis(&str[i]);
		if (i >  0 && str[i] == ')'
		&& str[i -1] == '$' && ft_isbacks(str, i - 2) == 0)
		{
			ft_putstr_fd("Erreur de syntaxe.", 2);
			ret = -1;
		}
		if (ret == -1)
			return (0);
		i += ret;
	}
	return (1);
}
