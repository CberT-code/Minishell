/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:28:04 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/14 18:36:56 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_find_c(char letter, char c)
{
	if (letter == c)
		return (1);
	return (0);
}

static int		ft_words(char *s, char c)
{
	int i;
	int nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (ft_find_c(s[i], c) == 1 && s[i])
			i++;
		if (s[i])
			nb_words++;
		while (ft_find_c(s[i], c) == 0 && s[i])
			i++;
	}
	return (nb_words);
}

static char		**ft_free(char **tab_words, int i)
{
	while (--i >= 0)
		free(tab_words[i]);
	free(tab_words);
	return (NULL);
}

static int		f_l(char *s, char c, int i)
{
	int count_l;

	count_l = 0;
	while (ft_find_c(s[i], c) == 0 && s[i++])
		count_l++;
	return (count_l);
}

char			**ft_split(char const *s, char c)
{
	char	**tab_words;
	int		nb_words;
	int		i;
	int		a;
	int		j;

	i = 0;
	a = 0;
	nb_words = ft_words((char *)s, c);
	if (!(tab_words = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	while (nb_words--)
	{
		j = 0;
		while (ft_find_c(s[a], c) == 1 && s[a])
			a++;
		if (!(tab_words[i] = malloc(sizeof(char) * (f_l((char *)s, c, a) + 1))))
			return (ft_free(tab_words, i));
		while (ft_find_c(s[a], c) == 0 && s[a])
			tab_words[i][j++] = s[a++];
		tab_words[i++][j] = '\0';
	}
	tab_words[i] = 0;
	return (tab_words);
}
