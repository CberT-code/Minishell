/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:28:04 by cbertola          #+#    #+#             */
/*   Updated: 2020/01/21 14:16:15 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free(char **tab_words, int i)
{
	while (--i >= 0)
		free(tab_words[i]);
	free(tab_words);
	return (NULL);
}

char			**ft_splitnum(char *s, int c)
{
	char	**tab_words;
	int		nb_words;
	int		i;
	int		a;
	int		j;

	i = 0;
	a = 0;
	nb_words = (ft_strlen(s) / c) + (ft_strlen(s) % c > 0 ? 1 : 0);
	if (!(tab_words = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	while (nb_words--)
	{
		j = 0;
		if (nb_words == 0 && (ft_strlen(s) % c > 0))
			c = ft_strlen(s) % c;
		if (!(tab_words[i] = malloc(sizeof(char) * c + 1)))
			return (ft_free(tab_words, i));
		while (j < c)
			tab_words[i][j++] = s[a++];
		tab_words[i++][j] = '\0';
	}
	tab_words[i] = 0;
	return (tab_words);
}
