/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:22:58 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/16 12:04:24 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s;
	unsigned char *t;

	s = (unsigned char *)s1;
	t = (unsigned char *)s2;
	while (n--)
		if (*s++ != *t++)
			return (*--s - *--t);
	return (0);
}
