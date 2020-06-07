/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:36:04 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/18 15:12:31 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = ft_strlen(dst);
	j = ft_strlen((char *)src);
	result = i + j;
	if (i > dstsize)
		return (dstsize + j);
	if (dstsize != 0)
		dstsize--;
	while (*src && i < dstsize && i < result + 1)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (result);
}
