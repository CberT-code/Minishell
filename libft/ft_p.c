/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:52:39 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:14:19 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_put_ptr2(unsigned long nb, t_flags *flags)
{
	char const		*base;
	int				i;
	int				rtn;
	char			result[12];

	base = "0123456789abcdef";
	i = 0;
	if (nb == 0 && flags->precis != -2)
		flags->rslt += ft_putchar_int('0');
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

int				ft_put_ptr(va_list ap, t_flags *flags)
{
	unsigned long		nb;
	int					nbc;

	nb = (unsigned long)va_arg(ap, void *);
	if (!nb)
		nb = 0;
	nbc = ft_count_char_int(nb, 16);
	if ((flags->width -= nbc + 2) > 0 && flags->arg & NUL)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	ft_putstr("0x");
	flags->rslt += 2;
	while (flags->arg & ZERO && (flags->width)-- > 0)
		flags->rslt += ft_putchar_int('0');
	flags->rslt += ft_put_ptr2(nb, flags);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}
