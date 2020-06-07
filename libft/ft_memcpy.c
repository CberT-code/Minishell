/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:27:22 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/24 12:25:34 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *s;
	unsigned char *t;

	if (!n || dst == src)
		return (dst);
	s = (unsigned char *)dst;
	t = (unsigned char *)src;
	while (n--)
		*s++ = *t++;
	return (dst);
}
