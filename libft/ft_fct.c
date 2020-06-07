/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:48:46 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:14:10 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_putchar_mod2(void)
{
	ft_putchar('%');
	return (1);
}

int				ft_putchar_mod(va_list ap, t_flags *flags)
{
	(void)ap;
	flags->precis = 0;
	flags->arg = flags->arg & ~(1 << 3);
	ft_init_mask(flags, 1, 10);
	flags->rslt += ft_display_before(flags, 1);
	flags->rslt += ft_putchar_mod2();
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}

int				ft_putzero(void)
{
	write(1, "0", 1);
	return (1);
}

int				ft_display_before(t_flags *flags, long int nb)
{
	int rslt;

	rslt = 0;
	if (flags->arg & POINT)
	{
		while (!(flags->arg & MINUS) && flags->width-- > 0)
			rslt += ft_putchar_int(' ');
		if (nb < 0)
			rslt += ft_putchar_int('-');
		while (flags->precis-- > 0)
			rslt += ft_putchar_int('0');
	}
	else
	{
		while (flags->arg & NUL && flags->width-- > 0)
			rslt += ft_putchar_int(' ');
		if (nb < 0)
			rslt += ft_putchar_int('-');
		while (flags->arg & ZERO && flags->width-- > 0)
			rslt += ft_putchar_int('0');
	}
	return (rslt);
}
