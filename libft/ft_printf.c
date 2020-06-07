/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:41:09 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 03:13:16 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_cleanstruct(t_flags *flags)
{
	flags->precis = -1;
	flags->width = 0;
	flags->arg = 0;
	return (1);
}

int		ft_printstr(char **str)
{
	int i;

	i = 0;
	while (*(*str) != '%' && *(*str) != '\0')
	{
		ft_putchar(*(*str)++);
		i++;
	}
	return (i);
}

int		ft_get_flags(char **str, t_flags *flags, va_list ap)
{
	if ((ft_isdigit(*(*str)) && *(*str) != '0') || *(*str) == '*')
		ft_width(ap, flags, &(*str), 0);
	if (*(*str) == '0')
		ft_width(ap, flags, &(*str), 1);
	if (*(*str) == '-')
		ft_width(ap, flags, &(*str), 2);
	if (*(*str) == '.')
		if (ft_precis(ap, flags, &(*str)) == 0)
			return (-1);
	return (1);
}

int		ft_get_fct(char **str, va_list ap, t_flags *flags)
{
	int			j;
	int			(*tab[9])(va_list, t_flags *);
	char		*tab_sign;

	tab[0] = &ft_putchar_ptf;
	tab[1] = &ft_putstr_int;
	tab[2] = &ft_put_ptr;
	tab[3] = &ft_putnbr_int;
	tab[4] = &ft_putnbr_int;
	tab[5] = &ft_putnbr_uint;
	tab[6] = &ft_puthexa_min;
	tab[7] = &ft_puthexa_max;
	tab[8] = &ft_putchar_mod;
	tab_sign = "cspdiuxX%";
	j = (ft_isfind(tab_sign, *(*str)));
	(*str)++;
	if (j == -1)
		return (1);
	return ((tab[j])(ap, flags));
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*str;
	t_flags		flags;

	va_start(ap, format);
	str = (char *)format;
	flags.rslt = 0;
	while (*str)
	{
		ft_cleanstruct(&flags);
		flags.rslt += ft_printstr(&str);
		if (*str == '%')
		{
			str++;
			if (!(ft_get_flags(&str, &flags, ap)))
				return (-1);
			if (!(ft_get_fct(&str, ap, &flags)))
				return (-1);
		}
	}
	va_end(ap);
	return (flags.rslt);
}
