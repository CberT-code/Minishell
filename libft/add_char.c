/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:44:57 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 17:53:25 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char        *add_char(char *str, char c, int i)
{
    char    *ret;
    int     j;

    j = -1;
    if (i > ft_strlen(str))
        i = ft_strlen(str);
    if (!(ret = calloc(sizeof(char), ft_strlen(str) + 2)))
        return (NULL);
    while (++j < i)
        ret[j] = str[j];
    ret[j] = c;
    if (i < ft_strlen(str))
        while (str[i])
            ret[++j] = str[i++];
    ret[++j] = '\0';
    return (ret);
}