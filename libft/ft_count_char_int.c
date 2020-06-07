/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 12:39:43 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/15 13:46:12 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_count_char_int(long int nb, int base)
{
	int			count;
	long int	i;

	if (base == 0)
		return (-1);
	count = 0;
	i = nb;
	if (i <= 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= base;
		count++;
	}
	return (count);
}
