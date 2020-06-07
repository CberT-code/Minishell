/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:44:25 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/21 15:01:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				u;
	unsigned int	i;
	char			*ptr;

	if (!(s))
		return (NULL);
	u = ft_strlen(s);
	i = 0;
	if (!(ptr = malloc(u * sizeof(char) + 1)))
		return (NULL);
	while (*s)
	{
		ptr[i] = (*f)(i, *s++);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
