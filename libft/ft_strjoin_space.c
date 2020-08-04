/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:27:36 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 17:55:51 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	char		*ptr;
	long int	u;
	long int	i;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	u = ft_strlen(s1) + ft_strlen(s2);
	if (!(ptr = calloc(u, (sizeof(char) + 2))))
		return (NULL);
	while (*s1)
		ptr[++i] = *s1++;
	ptr[++i] = ' ';
	while (*s2)
		ptr[++i] = *s2++;
	ptr[++i] = '\0';
	return (ptr);
}
