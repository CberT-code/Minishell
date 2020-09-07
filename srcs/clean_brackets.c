/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:25:45 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 19:53:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cpy_brackets(char *str, char *cpy, int *i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	(*i)++;
	while (ft_isbracket(str, *i) != 1 && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

char	*ft_clean_brackets(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& ft_isbacks(str, i - 1) == 0 && str[i + 1] == '{')
			ft_cpy_brackets(str, cpy, &i, &j);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}
