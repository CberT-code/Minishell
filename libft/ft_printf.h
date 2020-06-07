/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:54:11 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/13 11:34:49 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

/*
** 0|0|0|0|
** |.|-|0| |
*/
# define NUL 1
# define ZERO 2
# define MINUS 4
# define POINT 8

typedef struct	s_flags
{
	int			precis;
	int			width;
	char		arg;
	int			rslt;
}				t_flags;

int				ft_putchar_ptf(va_list ap, t_flags *flags);
int				ft_putstr_int(va_list ap, t_flags *flags);
int				ft_putnbr_int(va_list ap, t_flags *flags);
int				ft_putnbr_uint(va_list ap, t_flags *flags);
int				ft_puthexa_min(va_list ap, t_flags *flags);
int				ft_puthexa_max(va_list ap, t_flags *flags);
int				ft_put_ptr(va_list ap, t_flags *flags);
int				ft_putchar_mod(va_list ap, t_flags *flags);
int				ft_putzero(void);
int				ft_get_flags(char **str, t_flags *flags, va_list ap);
int				ft_get_fct(char **str, va_list ap, t_flags *flags);
int				ft_printf(const char *format, ...);
int				ft_printstr(char **str);
int				ft_precis(va_list ap, t_flags *flags, char **str);
void			ft_width(va_list ap, t_flags *flags, char **str, int i);
int				ft_count_char_int(long int nb, int base);
void			ft_init_mask(t_flags *flags, long int nb, int base);
int				ft_display_before(t_flags *flags, long int nb);

#endif
