/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:47:26 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/03 09:41:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char				*ptr;
	int					i;
	unsigned long int	u;

	i = -1;
	if (!(s))
		return (NULL);
	u = ft_strlen(s);
	if (start > u)
		len = 0;
	if (!(ptr = ft_calloc(len, sizeof(char) + 1)))
		return (NULL);
	while (s[start] && len--)
		ptr[++i] = s[start++];
	ptr[++i] = '\0';
	free(s);
	return (ptr);
}
