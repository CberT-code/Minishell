/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:52:35 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/19 17:38:09 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_strlen_str_quotes(char *s, char *str)
{
	int i;
	int j;

	i = 0;
	while (s && s[i])
	{
		j = 0;
		while (s[i] && str[j]){
			if (s[i] == str[j++] && ft_in_quotes(s, i) == 0)
			{
				printf("here we test -> %d\n", ft_in_quotes(s, i));
				return (i);
			}

		}
		i++;
	}
	return (i);
}

// int		main()
// {
// 	int i;
	
// 	i = ft_strlen_str_quotes("\"tutu lolo\"", " ");
// 	printf("here we test -> %d\n", i);
// }