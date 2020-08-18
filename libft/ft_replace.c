/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:21:44 by cyrillebert       #+#    #+#             */
/*   Updated: 2020/08/10 12:59:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h";

char		*ft_replace(char *str, char out, char in)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i == out])
			str[i] = in;
		i++;
	}
	return (str);
}
