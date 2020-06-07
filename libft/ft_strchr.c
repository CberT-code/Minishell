/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:55:23 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/10 11:35:22 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char *tab;

	tab = (char *)s;
	if (c == '\0')
	{
		while (*tab != c)
			tab++;
		return (tab);
	}
	while (*tab != c)
	{
		tab++;
		if (*tab == '\0')
			return (NULL);
	}
	return (tab);
}
