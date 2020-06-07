/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:49:03 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:14:00 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_putchar_ptf2(char c)
{
	ft_putchar(c);
	return (1);
}

int				ft_putchar_ptf(va_list ap, t_flags *flags)
{
	char		c;

	c = (char)va_arg(ap, int);
	flags->precis = 0;
	flags->arg = flags->arg & ~(1 << 3);
	ft_init_mask(flags, 1, 10);
	flags->rslt += ft_display_before(flags, 1);
	flags->rslt += ft_putchar_ptf2(c);
	if (flags->arg & MINUS)
		while ((flags->width)-- > 0)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}

static int		ft_putstr_int2(char *str, t_flags *flags)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (flags->arg & POINT)
		while (*str && flags->precis > i)
			i += ft_putchar_int(*str++);
	else
		while (*str)
			i += ft_putchar_int(*str++);
	return (i);
}

int				ft_putstr_int(va_list ap, t_flags *flags)
{
	char		*c;
	int			nb;

	c = va_arg(ap, char *);
	if (!c)
		c = "(null)";
	nb = ft_strlen(c);
	if (flags->arg & POINT)
		if (flags->precis < nb)
			nb = flags->precis;
	if (nb == -1)
		nb = 0;
	if (flags->arg & NUL)
		while (flags->width-- > nb)
			flags->rslt += ft_putchar_int(' ');
	flags->rslt += ft_putstr_int2(c, flags);
	if (flags->arg & MINUS)
		while (flags->width-- > nb)
			flags->rslt += ft_putchar_int(' ');
	return (1);
}
