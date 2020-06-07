/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:18:15 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/14 15:53:50 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *s;
	unsigned char *t;
	unsigned char u;

	s = (unsigned char *)dst;
	t = (unsigned char *)src;
	u = (unsigned char)c;
	while (n--)
	{
		*s++ = *t++;
		if (*(s - 1) == u)
			return (s);
	}
	return (NULL);
}
