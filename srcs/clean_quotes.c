/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 00:20:30 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 14:51:11 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	ft_isbacks(char *str, int i)
// {
// 	int cpt;

// 	cpt = 0;
// 	while (i >= 0 && str[i] == BACKS)
// 	{
// 		cpt++;
// 		i--;
// 	}
// 	if (cpt % 2 == 0)
// 		return (0);
// 	return (1);
// }

// int	ft_isquote(char *str, int i)
// {

// 	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == DOUBQ)
// 		return (2);
// 	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == SIMPQ)
// 		return (1);
// 	return (0);
// }

int		ft_travel_quotes(char *str, int i, char quote)
{
	int cpt;

	cpt = 0;
	while (i >= 0 && str[i] == quote)
	{
		cpt++;
		i--;
	}
	if (cpt % 2 == 0)
		return (0);
	return (1);
}

char	*ft_clean_quotes(char *str)
{
	int i;
	int j;
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
			if (i == ft_strlen(str) - 1 && str[i] != SIMPQ)
			{
				ft_printf("Simple quote missing.\n");
				return (NULL);
			}
			if (i < ft_strlen(str) - 1 && str[i + 1] == SIMPQ)
				i++;
			else
			{
				cpy[j++] = str[i++];
				while (ft_isquote(str, i) != 1 && str[i])
				{
					if (str[i] == BACKS && ft_isbacks(str, i) == 0)
						cpy[j++] = str[i];
					else if (str[i] != BACKS)
						cpy[j++] = str[i];
					i++;
				}
				if (str[i] != SIMPQ)
				{
					ft_printf("Simple quote missing.\n");
					return (NULL);
				}
				cpy[j++] = str[i];
			}
		}
		if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
		{
			if (i == ft_strlen(str) - 1 && str[i] != DOUBQ)
			{
				ft_printf("Double quote missing.\n");
				return (NULL);
			}
			if (i < ft_strlen(str) - 1 && str[i + 1] == DOUBQ)
				i++;
			else
			{
				cpy[j++] = str[i++];
				while (ft_isquote(str, i) != 2 && str[i])
				{
					if (str[i] == BACKS && ft_isbacks(str, i) == 0)
						cpy[j++] = str[i];
					else if (str[i] != BACKS)
						cpy[j++] = str[i];
					i++;
				}
				if (str[i] != DOUBQ)
				{
					ft_printf("Double quote missing.\n");
					return (NULL);
				}
				cpy[j++] = str[i];
			}
		}
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[j++] = str[i];
		else if (str[i] != BACKS)
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	printf("cpy -> %s\n", cpy);
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
// 	cpy = ft_clean_quotes(str);

// 	//ft_printf("after -> %s\n", cpy);
// 	return (0);
// }
