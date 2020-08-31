/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:21:09 by user42            #+#    #+#             */
/*   Updated: 2020/08/30 19:45:38 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_replace_ret(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((i == 0 && ft_strlen(str) > 2 && str[i] == '$' && str[i + 1] == '?')
			|| (i > 0 && i < ft_strlen(str) - 1 && str[i] == '$'
			&& str[i + 1] == '?' && ft_isbacks(str, i - 1) == 0))
		{
			len += ft_strlen(ft_itoa(g_ret));
			i++;
		}
		else
			len++;
	}
	return (len);
}

void	ft_fill_replace_ret(char *cpy, int *j, int *i)
{
	int k;
	char *cpy_ret;

	k = 0;
	cpy_ret = ft_strdup(ft_itoa(g_ret));
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	(*i)++;
	ft_strdel(&cpy_ret);
}

int		ft_len_brackets(char *str)
{
	int		brack;
	int		i;
	int		j;

	brack = 0;
	i = 0;
	j = 0;
	if (str[i] == '{')
	{
		i++;
		brack = 1;
	}
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
	&& str[i] != BACKS && str[i] != DOUBQ && str[i])
	{
		j++;
		i++;
	}
	if (brack == 1 && str[i - 1] != '}')
		return (0);
	j = (brack == 1) ? j - 1 : j;
	return (j);
}

char	*ft_check_brackets(char *str)
{
	int		brack;
	int		i;
	int		j;
	char	*cpy;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	brack = 0;
	i = 0;
	j = 0;
	if (str[i] == '{')
	{
		i++;
		brack = 1;
	}
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
	&& str[i] != BACKS && str[i] != '+' && str[i] != DOUBQ && str[i])
		cpy[j++] = str[i++];
	if (brack == 1 && str[i - 1] != '}')
		return (NULL);
	j = (brack == 1 || str[i - 1] == '}') ? j - 1 : j;
	cpy[j] = '\0';
	return (cpy);
}

int		ft_end_brackets(char *str)
{
	int i;
	int brack;

	i = 0;
	brack = 0;
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
	&& str[i] != BACKS && str[i] != '}' && str[i] != '+'
	&& str[i] != DOUBQ && str[i])
	{
		if (i > 0 && ft_isdigit(str[i - 1]) == 1)
			break;
		if (str[i] == '{')
			brack = 1;
		i++;
	}
	i = (brack == 1 && str[i] == '}') ? i + 1 : i;
	return (i);
}

int		ft_end_brackets_doubq(char *str)
{
	int i;
	int brack;

	i = 0;
	brack = 0;
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
	&& str[i] != BACKS && str[i] != '}' && str[i] != '+'
	&& str[i])
	{
		if (i > 0 && ft_isdigit(str[i - 1]) == 1)
			break;
		if (str[i] == '{')
			brack = 1;
		i++;
	}
	i = (brack == 1 && str[i] == '}') ? i + 2 : i;
	return (i);
}
