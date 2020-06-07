/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:27:47 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/14 15:54:24 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *r;

	r = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)c == *r)
			return (r);
		r++;
	}
	return (NULL);
}
