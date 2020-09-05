/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:15:05 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 15:48:37 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

unsigned long long int		ft_atoi_long(const char *str)
{
	unsigned long long int result;

	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' ||
			*str == '\r' || *str == 32)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		result *= 10;
		result += (*str - 48);
		str++;
	}
	return (result);
}
