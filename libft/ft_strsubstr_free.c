/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubstr_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:30:49 by cbertola          #+#    #+#             */
/*   Updated: 2020/01/20 23:08:35 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_bzero_tab(int *tab)
{
	int i;

	i = 256;
	while (i--)
		tab[i] = 0;
}

char		*ft_strsubstr_free(char *s1, char *sub)
{
	int		i;
	int		j;
	char	*s3;
	int		tab[256];

	ft_bzero_tab(tab);
	j = 0;
	i = ft_strlen(s1) - ft_how_many(s1, sub);
	if (!(s3 = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (*sub)
	{
		tab[(int)*sub] = 1;
		sub++;
	}
	while (s1[i])
	{
		if (tab[(int)s1[i]] == 0)
			s3[j++] = s1[i];
		i++;
	}
	s3[j] = '\0';
	free(s1);
	return (s3);
}
