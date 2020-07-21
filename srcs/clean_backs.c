/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_backs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 14:25:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isbacks(char *str, int i)
{
	int cpt;

	cpt = 0;
	while (i >= 0 && str[i] == BACKS)
	{
		cpt++;
		i--;
	}
	if (cpt % 2 == 0)
		return (0);
	return (1);
}

int	ft_isquote(char *str, int i)
{

	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == DOUBQ)
		return (2);
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == SIMPQ)
		return (1);
	return (0);
}

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
	{
		if (*i > 0 && str[*i] == BACKS && ft_isbacks(str, (*i) - 1) == 1)
			(*i)++;
		cpy[(*j)++] = str[(*i)++];
	}
}

char	*ft_clean_backs(char *str)
{
	int i;
	int j;

	char *cpy;

	if (!(cpy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
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
	printf("cpy -> |%s|\n", cpy);
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
	cpy = ft_clean_backs(str);
	//ft_printf("after -> %s\n", cpy);
	return (0);
}