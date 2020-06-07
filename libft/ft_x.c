/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:35:46 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:11:45 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_puthexa_minb(unsigned int nb, t_flags *flags)
{
	char const		*base;
	int				i;
	int				rtn;
	char			result[9];

	base = "0123456789abcdef";
	i = 0;
	if (nb == 0 && (flags->precis != -1 || !(flags->arg & POINT)))
		return (ft_putchar_int('0'));
	while (nb > 0)
	{
		result[i++] = base[nb % 16];
		nb = nb / 16;
	}
	rtn = i;
	while (i > 0)
		ft_putchar(result[--i]);
	return (rtn);
}

int				ft_puthexa_min(va_list ap, t_flags *flags)
{
	unsigned int		nb;

	nb = va_arg(ap, unsigned int);
	ft_init_mask(flags, nb, 16);
	flags->rslt += ft_display_before(flags, nb);
	flags->rslt += ft_puthexa_minb(nb, flags);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}

static int		ft_puthexa_maxb(unsigned int nb, t_flags *flags)
{
	char const		*base;
	int				i;
	int				rtn;
	char			result[9];

	base = "0123456789ABCDEF";
	i = 0;
	if (nb == 0 && (flags->precis != -1 || !(flags->arg & POINT)))
		return (ft_putchar_int('0'));
	while (nb > 0)
	{
		result[i++] = base[nb % 16];
		nb = nb / 16;
	}
	rtn = i;
	while (i > 0)
		ft_putchar(result[--i]);
	return (rtn);
}

int				ft_puthexa_max(va_list ap, t_flags *flags)
{
	unsigned int		nb;

	nb = va_arg(ap, unsigned int);
	ft_init_mask(flags, nb, 16);
	flags->rslt += ft_display_before(flags, nb);
	flags->rslt += ft_puthexa_maxb(nb, flags);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}
