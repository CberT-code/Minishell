/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:21:09 by user42            #+#    #+#             */
/*   Updated: 2020/08/31 19:35:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_replace_ret(char *str)
{
	int	i;
	int	len;
	char *cpy;

	i = -1;
	len = 0;
	cpy = NULL;
	while (str[++i])
	{
		if ((i == 0 && ft_strlen(str) > 2 && str[i] == '$' && str[i + 1] == '?')
			|| (i > 0 && i < ft_strlen(str) - 1 && str[i] == '$'
			&& str[i + 1] == '?' && ft_isbacks(str, i - 1) == 0))
		{
			cpy = ft_itoa(g_ret);
			len += ft_strlen(cpy);
			i++;
			ft_strdel(&cpy);
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
	cpy_ret = ft_itoa(g_ret);
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	(*i)++;
	ft_strdel(&cpy_ret);
}