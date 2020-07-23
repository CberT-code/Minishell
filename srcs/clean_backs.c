/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_backs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:15:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
// 	cpy = ft_clean_backs(str);
// 	//ft_printf("after -> %s\n", cpy);
// 	return (0);
// }