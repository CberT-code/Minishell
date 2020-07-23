/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:24:25 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/23 17:14:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long int i;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack != '\0' && len > 0)
	{
		i = 0;
		while (needle[i] == haystack[i] && (len - i))
			if (needle[++i] == '\0')
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
