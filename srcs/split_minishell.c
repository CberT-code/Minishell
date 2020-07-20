/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 14:31:06 by user42            #+#    #+#             */
/*   Updated: 2020/07/20 11:59:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ischar(char *str, int i, char c)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == c)
		return (1);
	return (0);
}

int		ft_nb_words(char *str, char c)
{
	int i;
	int nb_words;

	i = -1;
	nb_words = 0;

	while (str[++i])
	{
		while (((i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == c)
		|| (i == 0 && str[i] == c)) && str[i])
			i++;
		if (i < ft_strlen(str))
			nb_words++;
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
		{
			i++;
			while (ft_isquote(str, i) != 1 && str[i])
				i++;
		}
		if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
		{
			i++;
			while (ft_isquote(str, i) != 1 && str[i])
				i++;
		}
		while ((ft_ischar(str, i, c) != 1 || (i == 0 && str[i] == c)) && str[i])
			i++;
		printf("nb_words -> %d\n", nb_words);
	}
	return (nb_words);
}


char	**ft_split_minishell(char *str, char c)
{
	int i;
	char **tab;
	
	i = -1;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_nb_words(str, c) + 1))))
		return (NULL);
	/*while (str[++i])
	{
		
	}*/
	return (tab);
}

int		main(int argc, char **argv, char **env)
{
	char *str;
	int		fd;
	char **tab;

	str = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
	tab = ft_split_minishell(str, ' ');
	//ft_printf("after -> %s\n", cpy);
	return (0);
}
