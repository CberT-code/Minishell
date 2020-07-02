/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpyfrom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:12:28 by cbertola          #+#    #+#             */
/*   Updated: 2020/06/25 11:48:58 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char            *ft_strcpyfrom(const char *src, char *n)
{
    char     *dst;
    int      i;
    int      j;
    int      nb;

    i = 0;

    nb = ft_strlen(src) - ft_strlen_str(src, n);
    if (!(dst = malloc(sizeof(char) * nb + 1)))
        return (NULL);
    j = ft_strlen_str(src, n) + 1;
    while (src[j])
        dst[i++] = src[j++];
    dst[i] = 0;
    return (dst);
}