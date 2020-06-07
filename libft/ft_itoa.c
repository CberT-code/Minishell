/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:37:40 by cbertola          #+#    #+#             */
/*   Updated: 2019/10/24 15:36:05 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_count_c(long int n, int i)
{
	if (n < 0)
		n *= -1;
	if (n >= 10)
		return (ft_count_c(n / 10, ++i));
	return (i);
}

static char			ft_reverse(char *s)
{
	char	swap[15];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		swap[i] = s[i];
		i++;
	}
	s[i] = '\0';
	while (i)
		s[--i] = swap[j++];
	return (*s);
}

static char			ft_process(char *s, long int nbr)
{
	int i;

	i = 0;
	while (nbr > 0)
	{
		s[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	s[++i] = '\0';
	*s = ft_reverse(s);
	return (*s);
}

char				*ft_itoa(int n)
{
	char		*ptr;
	int			i;
	long int	nbr;

	nbr = n;
	i = ft_count_c(nbr, 1);
	i = n < 0 ? i + 1 : i;
	if (!(ptr = malloc(i + 1 * sizeof(char))))
		return (NULL);
	if (nbr == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	if (nbr < 0)
	{
		nbr *= -1;
		ptr[--i] = '-';
	}
	*ptr = ft_process(ptr, nbr);
	return (ptr);
}
