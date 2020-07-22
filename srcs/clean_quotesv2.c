/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotesv2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 00:20:30 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 16:54:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_clean_squotes(char *str, char *cpy, int*i, int *j)
{
	if (*i < ft_strlen(str) - 1 && str[(*i) + 1] == SIMPQ)
		(*i) += 2;
	else
	{
		cpy[(*j)++] = str[(*i)++];
		while (ft_isquote(str, *i) != 1 && str[(*i)])
			cpy[(*j)++] = str[(*i)++];
		if (str[*i] != SIMPQ)
			return (-1);
		cpy[(*j)++] = str[(*i)++];
	}
	return (0);
}

int	ft_clean_dbquotes(char *str, char *cpy, int*i, int *j)
{
	if (*i < ft_strlen(str) - 1 && str[(*i) + 1] == DOUBQ)
		(*i) += 2;
	else
	{
		cpy[(*j)++] = str[(*i)++];
		while (ft_isquote(str, *i) != 2 && str[(*i)])
			cpy[(*j)++] = str[(*i)++];
		if (str[*i] != DOUBQ)
			return (-1);
		cpy[(*j)++] = str[(*i)++];
	}
	return (0);
}

char	*ft_clean_quotes(char*str)
{
	int i;
	int j;
	int ret;
	char *cpy;
	
	i = -1;
	j = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
		{
			if ((ret = ft_clean_squotes(str, cpy, &i, &j)) == -1)
				ft_printf("Simple quote missing.\n");
		}
		if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
		{
			if ((ret = ft_clean_dbquotes(str, cpy, &i, &j)) == -1)
				ft_printf("Double quote missing.\n");
		}
		cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	printf("cpy -> %s\n", cpy);
	return (cpy);
}
/*
int		main(int argc, char **argv, char **env)
{
	char *str;
	int		fd; 
	char *cpy;

	str = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
	cpy = ft_clean_quotes(str);

	//ft_printf("after -> %s\n", cpy);
	return (0);
}*/
