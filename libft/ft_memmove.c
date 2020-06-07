/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:55:11 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/24 12:21:30 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *s;
	unsigned char *t;

	s = (unsigned char *)dst;
	t = (unsigned char *)src;
	if (!len || src == dst)
		return (dst);
	if (dst < src)
	{
		while (len--)
			*s++ = *t++;
	}
	else
	{
		s = s + len - 1;
		t = t + len - 1;
		while (len--)
			*s-- = *t--;
	}
	return (dst);
}
