/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:15:51 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		cpy[(*j)++] = str[(*i)++];
}

void	ft_travel_spaces(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	(*i)--;
}

int		ft_start(char *str)
{
	int i = 0;

	while (((i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == ' ')
	|| (i == 0 && str[i] == ' ')) && str[i])
		i++;
	return (i);
}

int		ft_end(char *str)
{
	int k;
	
	k = ft_strlen(str) - 1;
	
	while (k > 0 && ft_isbacks(str, k - 1) == 0 && str[k] == ' ')
		k--;
	return (k);
}

char	*ft_clean_spaces(char *str)
{
	int i;
	int j;
	char *cpy;

	if (!(cpy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	i = ft_start(str);
	j = 0;
	while (i <= ft_end(str))
	{
		if ((i > 0 && str[i] == ' ' &&  ft_isbacks(str, i - 1) == 0))
			ft_travel_spaces(str, &i);
		else if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_cpy_in_squotes(str, cpy, &i, &j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			ft_cpy_in_dbquotes(str, cpy, &i, &j);
		cpy[j++] = str[i++];
	}
	cpy[j] = '\0';
	return (cpy);
}


// int		main(int argc, char **argv, char **env)
// {
// 	char *str;
// 	int		fd;
// 	char *cpy;

// 	str = NULL;
// 	fd = 0;
// 	get_next_line(fd, &str);
// 	close(fd);
// 	cpy = ft_clean_spaces(str);
// 	cpy = ft_clean_backs(cpy);
// 	//ft_printf("after -> %s\n", cpy);
// 	return (0);
// }