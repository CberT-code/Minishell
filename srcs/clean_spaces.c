/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_spacesv2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/16 12:56:58 by user42           ###   ########.fr       */
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

int	ft_cpy_in_quotes(char *str, char *cpy, int *j, int quote)
{
	int i;

	i = 0;
	cpy[(*j)++] = str[i++];
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

void	ft_travel_spaces(char *str, char *cpy, int *i, int *j)
{
	cpy[(*j)++] = str[(*i)++];
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	(*i)--;
}

char	*ft_clean_spaces(char *str)
{
	int i;
	int j;
	char *cpy;

	str = ft_strtrim(str, " ");
	if (!(cpy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			i += ft_cpy_in_quotes(&str[i], cpy, &j, 1);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			i += ft_cpy_in_quotes(&str[i], cpy, &j, 2);
		if ((i > 0 && str[i] == ' ' &&  ft_isbacks(str, i - 1) == 0))
			ft_travel_spaces(str, cpy, &i, &j);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[j++] = str[i];
		else if (str[i] != BACKS)
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	printf("cpy -> %s\n", cpy);
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
	cpy = ft_clean_spaces(str);
	//ft_printf("after -> %s\n", cpy);
	return (0);
}