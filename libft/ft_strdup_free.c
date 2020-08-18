/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:24:45 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/18 15:50:36 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char *s1)
{
	char	*ptr;
	int		i;

	if (!s1)
	{
		free(s1);
		return (NULL);
	}
	i = ft_strlen(s1);
	if (!(ptr = calloc(i, sizeof(char) + 1)))
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}
