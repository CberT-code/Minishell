/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_semicol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:16:22 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_semicol			*ft_lstnewsemicol(char *str, char **env)
{
	t_semicol *semicol;
	
	if (!(semicol = (t_semicol*)malloc(sizeof(t_semicol))))
		return (NULL);
	semicol->str = str;
	semicol->pipes = split_pipes(semicol->str, env);
	semicol->next = NULL;
	return (semicol);
}

t_semicol			*ft_lstlastsemicol(t_semicol *semicol)
{
	if (!semicol)
		return (NULL);
	while (semicol->next)
		semicol = semicol->next;
	return (semicol);
}

void			lstadd_back_semicol(t_semicol **semicol, char *str, char **env)
{
	if (*semicol != NULL)
		ft_lstlastsemicol(*semicol)->next = ft_lstnewsemicol(str, env);
	else
		*semicol = ft_lstnewsemicol(str, env);
}
