/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:25:45 by user42            #+#    #+#             */
/*   Updated: 2020/08/31 19:49:15 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cpy_brackets(char *str, char *cpy, int *i, int *j)
{
	if (*i > 0 && str[(*i) - 1] == '$')
	{
		(*i)++;
		while (ft_isbracket(str, *i) != 1 && str[*i])
			cpy[(*j)++]= str[(*i)++];
	}
}

char *ft_clean_brackets(char *str)
{
	int i;
	int j;
	char *cpy;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '{')
			ft_cpy_brackets(str, cpy, &i, &j);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	//ft_strdel(&str);
	return (cpy);
}
/*
int		main(int argc, char **argv, char **env)
{
	char 	*str;
	int		fd;

	str = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
	printf("%s\n", ft_clean_brackets(str));
	//ft_printf("after -> %s\n", cpy);
	return (0);
}*/