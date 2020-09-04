/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:15:05 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 16:59:23 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int		ft_atoi_long(const char *str)
{
	long int n;
	long int result;

	n = 1;
	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' ||
			*str == '\r' || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			n = -1;
	while (*str >= 48 && *str <= 57)
	{
		result *= 10;
		result += (*str - 48);
		str++;
	}
	return (n * result);
}
