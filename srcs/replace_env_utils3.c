/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:21:09 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 01:00:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_simpq_cpy_all(char *str, char *cpy, int *i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	while (str[*i] != SIMPQ && str[*i])
		cpy[(*j)++] = str[(*i)++];
	cpy[(*j)++] = str[*i];
}

int		ft_len_word(char *str, int *len)
{
	int		i;
	char	*cpy;

	i = 1;
	while (ft_iscrochet(str, i) != 1 && str[i])
		i++;
	cpy = ft_strndup(&str[1], i - 1);
	len += ft_atoi(cpy);
	ft_strdel(&cpy);
	return (i);
}

int		ft_len_crochets(char *str)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_len(str, &i, &len);
		else if (i > 0 && str[i] == '[' && str[i - 1] == '$'
		&& ft_isbacks(str, i - 2) == 0)
			i += ft_len_word(&str[i], &len);
		else
			len++;
	}
	return (len);
}

int		ft_fill_replace_word(char *str, char *cpy, int *j)
{
	int		i;
	int		k;
	char	*cpy2;

	i = 2;
	while (ft_iscrochet(str, i) != 1 && str[i])
		i++;
	cpy2 = ft_strndup(&str[2], i - 1);
	k = ft_atoi(cpy2);
	ft_strdel(&cpy2);
	cpy2 = ft_itoa(k);
	k = 0;
	while (cpy2[k])
		cpy[(*j)++] = cpy2[k++];
	ft_strdel(&cpy2);
	return (i);
}

char	*ft_replace_crochets(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_len_crochets(str) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '[' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_word(&str[i], &cpy[0], &j);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}
