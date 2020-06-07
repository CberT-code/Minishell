/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:27:36 by cbertola          #+#    #+#             */
/*   Updated: 2020/01/21 16:14:24 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int k)
{
	char		*ptr;
	int			u;
	long int	i;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	u = ft_strlen(s1) + ft_strlen(s2);
	if (!(ptr = malloc(u * (sizeof(char) + 1))))
		return (NULL);
	u = 0;
	while (s1[u])
		ptr[++i] = s1[u++];
	u = 0;
	while (s2[u])
		ptr[++i] = s2[u++];
	ptr[++i] = '\0';
	if (*s1 && (k == 1 || k == 3))
		free(s1);
	if (*s2 && (k == 2 || k == 3))
		free(s2);
	return (ptr);
}
