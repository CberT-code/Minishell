/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subfromstr_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:47:26 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/03 09:41:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_subfromstr_free(char *s, int start, int len)
{
	char				*ptr;
	int					i;
	int					u;

	i = -1;
	if (!(s))
		return (NULL);
	u = ft_strlen(s);
	if (start > u)
		len = 0;
	if (len + start > u)
		len = u - start;
	u -= len;
	if (!(ptr = ft_calloc(u, sizeof(char) + 1)))
		return (NULL);
	while (++i < start)
		ptr[i] = s[i];
	u = i;
	while (len--)
		i++;
	while (s[i])
		ptr[u++] = s[i++];
	ptr[u] = '\0';
	free(s);
	return (ptr);
}
