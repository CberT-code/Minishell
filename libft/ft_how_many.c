/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_how_many.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:44:08 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/23 17:13:48 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_how_many(char *str, char *tab)
{
	int i;
	int j;

	j = 0;
	while (*str)
	{
		i = 0;
		while (tab[i])
		{
			if (tab[i] == *str)
				j++;
			i++;
		}
		str++;
	}
	return (j);
}
