/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:00:50 by cbertola          #+#    #+#             */
/*   Updated: 2020/06/25 16:13:27 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	if (*s1 || *s2)
	{
		while ((*s1 || *s2))
		{
			if (*s1 != *s2)
				return ((unsigned char)*s1 - (unsigned char)*s2);
			s1++;
			s2++;
		}
	}
	return (0);
}
