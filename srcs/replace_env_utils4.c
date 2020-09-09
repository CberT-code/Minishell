/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:21:09 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 00:58:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_replace_value2(char *str, t_gbl *gbl)
{
	int		i;
	int		len;
	char	*cpy;

	i = -1;
	len = 0;
	cpy = NULL;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_len(str, &i, &len);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& (str[i + 1] == '#' || str[i + 1] == '-')
		&& ft_isbacks(str, i - 1) == 0)
		{
			cpy = (str[i + 1] == '#') ? ft_itoa(gbl->argc - 1)
			: ft_strdup("himBHs");
			len += ft_strlen(cpy);
			i++;
			ft_strdel(&cpy);
		}
		else
			len++;
	}
	return (len);
}

int		ft_fill_replace_value2(char *cpy, int *j, char c, t_gbl *gbl)
{
	int		k;
	char	*cpy_ret;
	int		i;

	i = 0;
	k = 0;
	cpy_ret = (c == '#') ? ft_itoa(gbl->argc - 1)
	: ft_strdup("himBHs");
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	i++;
	ft_strdel(&cpy_ret);
	return (i);
}

char	*ft_replace_value2(char *str, t_gbl *gbl)
{
	char	*cpy;
	int		i;
	int		j;

	if (!(cpy = (char*)malloc(sizeof(char) *
	(ft_len_replace_value2(str, gbl) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '#' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value2(&cpy[0], &j, '#', gbl);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '-' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value2(&cpy[0], &j, '-', gbl);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}
