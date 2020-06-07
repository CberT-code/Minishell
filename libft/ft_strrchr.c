/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:55:12 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/15 11:58:44 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *tab;
	char *tab2;

	tab = (char *)s;
	tab2 = NULL;
	if (c == '\0')
	{
		while (*tab != c)
			tab++;
		return (tab);
	}
	while (*tab != '\0')
	{
		if (*tab == c)
			tab2 = tab;
		tab++;
	}
	if (!(tab2))
		return (NULL);
	return (tab2);
}
