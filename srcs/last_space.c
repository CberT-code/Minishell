/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/06/19 13:50:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_in_quotes(char *str, int i)
{
	int quote;
	int dbquote;
	int j;
	int last;

	quote = 0;
	dbquote = 0;
	last = 0;
	j = -1;
	while (++j < i)
	{
		if (j > 0 && str[j] == 39 && str[j - 1] != '\\')
		{
			quote++;
			last = 1;
		}
		if (j > 0 && str[j] == 34 && str[j - 1] != '\\')
		{
			dbquote++;
			last = 2;
		}
	}
	if (quote % 2 != 0 || dbquote % 2 != 0)
		return(last);
	return(0);	
}

char	*ft_last_space(char *str)
{
	int i;
	int j;
	char *cpy;
	int	start;

	if (!str)
		return (NULL);
	if (!(cpy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && ft_in_quotes(str, i) == 0)
		{
			cpy[j++] = ' ';
			start = i;
			while (str[i] == ' ')
				i++;
		}
		cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	return (cpy);
}

int main(void)
{
	printf("%s\n",ft_last_space("test       \'de   	  la\'      fonction"));
	return (0);
}