/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_spaces_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:12:03 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/21 13:52:56 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_multiple_char_nq(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == c && ft_in_quotes(str, i) == 0)
			j++;
		i++;
	}
	return (j);
}

char	*clean_multiple_char_nq(char *str, char c)
{
	char *str2;
	int i;
	int j;

	i = -1;
	j = -1;
	if (!(str2 = malloc(sizeof(char) * count_multiple_char_nq(str, c) + 1)))
		return (NULL);
	while (str[++i])
	{
		while (str[i] == c && str[i + 1] == c && ft_in_quotes(str, i) == 0)
			i++;
		str2[++j] = str[i];
	}
	return (str2);
}

char	*ft_clean_spaces(char *str)
{
	int 	i;
	char 	*str2;

	i = 0;

	while (str[i] == ' ')
		i++;
	str2 = ft_substr(str, i, ft_strlen(str));
	str2 = clean_multiple_char_nq(str2, ' ');
	i = ft_strlen(str2) - 1;
	while (i == ' ')
		i--;
	str2 = ft_substr_free(str2, 0, i);
	
	return (str2);
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
	ft_printf("after -> |%s|\n", cpy);
	return (0);
}