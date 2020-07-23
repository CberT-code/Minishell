/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:21:44 by cyrillebert       #+#    #+#             */
/*   Updated: 2020/07/23 17:14:16 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h";

char       *ft_replace(char *str, char out, char in)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i == out])
            str[i] = in;
        i++;
    }
    return (str);
}