/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:48:00 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 10:49:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_replace_value(char *str, t_gbl *gbl)
{
	int		i;
	int		len;
	char	*c;

	i = -1;
	len = 0;
	c = NULL;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_len(str, &i, &len);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& (str[i + 1] == '?' || str[i + 1] == '$')
		&& ft_isbacks(str, i - 1) == 0)
		{
			c = (str[i + 1] == '?') ? ft_itoa(gbl->ret) : ft_itoa(gbl->pid - 1);
			len += ft_strlen(c);
			i++;
			ft_strdel(&c);
		}
		else
			len++;
	}
	return (len);
}

int		ft_fill_replace_value(char *cpy, int *j, char c, t_gbl *gbl)
{
	int		k;
	char	*cpy_ret;
	int		i;

	i = 0;
	k = 0;
	cpy_ret = (c == '?') ? ft_itoa(gbl->ret) : ft_itoa(gbl->pid - 1);
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	i++;
	ft_strdel(&cpy_ret);
	return (i);
}

char	*ft_replace_value(char *str, t_gbl *gbl)
{
	char	*cpy;
	int		i;
	int		j;

	if (!(cpy = (char*)malloc(1 * (ft_len_replace_value(str, gbl) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '?' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value(&cpy[0], &j, '?', gbl);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '$' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value(&cpy[0], &j, '$', gbl);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}

int		ft_find_size_arg(char *str)
{
	int i;

	i = 0;
	while (str[i] != '#' && str[i] != '-' && str[i] != '='
	&& str[i] != '+' && str[i] != '}' && str[i] != '.'
	&& str[i] != '/' && str[i] != ',' && str[i] != '%'
	&& str[i] != ']' && str[i] != ':' && str[i] != BACKS
	&& str[i] != DOUBQ && str[i] != SIMPQ && str[i] != ' '
	&& str[i] != '^' && ft_isdigit(str[i]) == 0 && str[i])
		i++;
	return (i);
}
