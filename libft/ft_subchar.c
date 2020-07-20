/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:21:44 by cyrillebert       #+#    #+#             */
/*   Updated: 2020/07/20 11:47:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int  count_char(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i == c])
            count++;
        i++;
    }
    return (count);
}
char        *ft_subchar(char *str, char c)
{
    char    *ret;
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (!(ret = malloc(sizeof(char) * (ft_strlen(str) - count_char(str, c)) + 1)))
        return (NULL);
    while (str[i])
    {
        if (str[i] == c)
            i++;
        ret[j++] = str[i++];
    }
    free(str);
    return (ret);
}