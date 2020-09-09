/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_backs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 10:38:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cpy_in_squotes(char *str, char *cpy, int *i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	while (ft_isquote(str, *i) != 1 && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

void	ft_cpy_in_dbquotes(char *str, char *cpy, int *i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	while (ft_isquote(str, *i) != 2 && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

char	*ft_clean_backs(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	if (!(cpy = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_cpy_in_squotes(str, cpy, &i, &j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			ft_cpy_in_dbquotes(str, cpy, &i, &j);
		if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[j++] = str[i];
		else if (str[i] != BACKS)
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	return (cpy);
}
