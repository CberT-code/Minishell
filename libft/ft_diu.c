/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:20:09 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:16:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_putnbr_intb(int nb, t_flags *flags)
{
	int					i;
	int					j;
	int					result[11];
	long int			nbr;

	nbr = nb;
	i = 0;
	j = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr == 0 && (flags->precis != -1 || !(flags->arg & POINT)))
		return (ft_putchar_int('0'));
	while (nbr > 0)
	{
		result[i++] = nbr % 10;
		nbr /= 10;
	}
	j += i;
	while (i >= 1)
		ft_putchar(result[--i] + '0');
	return (j);
}

int				ft_putnbr_int(va_list ap, t_flags *flags)
{
	int					nb;

	nb = va_arg(ap, int);
	ft_init_mask(flags, nb, 10);
	flags->rslt += ft_display_before(flags, nb);
	flags->rslt += ft_putnbr_intb(nb, flags);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}

static int		ft_putnbr_uintb(unsigned int nb, t_flags *flags)
{
	int					i;
	int					j;
	int					result[11];

	i = 0;
	if (nb == 0 && (flags->precis != -1 || !(flags->arg & POINT)))
		return (ft_putchar_int('0'));
	while (nb > 0)
	{
		result[i++] = nb % 10;
		nb /= 10;
	}
	j = i;
	while (i >= 1)
		ft_putchar(result[--i] + '0');
	return (j);
}

int				ft_putnbr_uint(va_list ap, t_flags *flags)
{
	unsigned int		nb;

	nb = va_arg(ap, unsigned int);
	ft_init_mask(flags, nb, 10);
	flags->rslt += ft_display_before(flags, nb);
	flags->rslt += ft_putnbr_uintb(nb, flags);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}
