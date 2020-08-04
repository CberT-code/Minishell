/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:50:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 17:55:04 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    ft_charup(char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

char    *ft_strup(char *str)
{
    char *strup;
    int i;

    if (!(strup = calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    while (str[i])
    {
        strup[i] = ft_charup(str[i]);
        i++;
    }
    free(str);
    return (strup);
}