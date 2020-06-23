/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:22:09 by cbertola          #+#    #+#             */
/*   Updated: 2020/06/23 18:26:25 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen_str(const char *s, char *str)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (str[j])
			if (s[i] == str[j++])
				return (i);
		i++;
	}
	return (i);
}
