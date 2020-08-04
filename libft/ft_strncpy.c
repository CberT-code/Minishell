/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:20:30 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 17:55:04 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char            *ft_strncpy(const char *src, int n)
{
    char        *dst;
    int      i;

    if (!(dst = calloc(sizeof(char), n + 1)))
        return (NULL);
    i = 0;
    if (n)
    {
        while (i < n && (dst[i] = src[i]))
            i++;
        while (i < n)
            dst[i++] = 0;
    }
    return (dst);
}