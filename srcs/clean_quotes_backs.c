/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes_backs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:38:57 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 16:07:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quote_len(char *str, int *i, int *len, int quote)
{
	(*i)++;
	while (ft_isquote(str, *i) != quote && str[*i])
	{
		if (str[*i] == BACKS && ft_isbacks(str, *i) == 0)
			(*len)++;
		else if (str[*i] != BACKS)
			(*len)++;
		(*i)++;
	}
}

int		ft_cpylen(char *str)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_quote_len(str, &i, &len, 1);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			ft_quote_len(str, &i, &len, 2);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			len++;
		else if (str[i] != BACKS)
			len++;
	}
	return (len);
}

int		ft_quotes_cpy(char	*str, char *cpy, int *j, int quote)
{
	int i;

	i = 1;
	while (ft_isquote(str, i) != quote && str[i])
	{
		if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[(*j)++] = str[i];
		else if (str[i] != BACKS)
			cpy[(*j)++] = str[i];
		i++;
	}
	return (i);
}

char	*ft_clean_quotes_backs(char *str)
{
	int i;
	int j;
	char *cpy;

	i = -1;
	j = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_cpylen(str) + 1))))
		return (NULL);
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			i += ft_quotes_cpy(&str[i], cpy, &j, 1);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			i += ft_quotes_cpy(&str[i], cpy, &j, 2);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[j++] = str[i];
		else if (str[i] != BACKS)
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	//printf("cpy -> %s\n", cpy);
	return (cpy);
}

int		main(int argc, char **argv, char **env)
{
	char *str;
	int		fd;
	char *cpy;

	str = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
	cpy = ft_clean_quotes_backs(str);
	//ft_printf("after -> %s\n", cpy);
	return (0);
}
