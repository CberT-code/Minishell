/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 00:20:30 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:15:50 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_clean_squotes(char *str, char *cpy, int*i, int *j)
{

	cpy[(*j)++] = str[(*i)++];
	while (ft_isquote(str, *i) != 1 && str[(*i)])
	{
		if ( *i > 0 && str[*i] == SIMPQ && ft_isbacks(str, (*i) - 1) == 1)
			return (1);
		cpy[(*j)++] = str[(*i)++];
	}
	if (str[*i] != SIMPQ)
		return (-1);
	cpy[(*j)++] = str[(*i)];
	return (0);
}

int	ft_clean_dbquotes(char *str, char *cpy, int*i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	while (ft_isquote(str, *i) != 2 && str[(*i)])
		cpy[(*j)++] = str[(*i)++];
	if (str[*i] != DOUBQ)
		return (-1);
	cpy[(*j)++] = str[(*i)];
	return (0);
}

char *ft_squotes_error(char **cpy)
{
	if (cpy)
	{
		if (*cpy)
			free(*cpy);
		*cpy = NULL;
	}
	ft_printf("Simple quote missing.\n");
	return (NULL);
}

char *ft_dbquotes_error(char **cpy)
{
	if (cpy)
	{
		if (*cpy)
			free(*cpy);
		*cpy = NULL;
	}
	ft_printf("Double quote missing.\n");
	return (NULL);
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
				return (ft_squotes_error(&cpy));
		}
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
		{
			if ((ret = ft_clean_dbquotes(str, cpy, &i, &j)) == -1)
				return (ft_dbquotes_error(&cpy));
		}
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
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
	return (0);
}*/
