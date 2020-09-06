/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_semicol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 09:27:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/06 09:27:49 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_semi		*ft_lstnewsemi(t_gbl *gbl, char *str)
{
	t_semi *semi;

	if (!(semi = (t_semi*)ft_calloc(sizeof(t_semi), 1)))
		return (NULL);
	semi->str = str;
	semi->pipes = split_pipes(gbl, semi);
	semi->next = NULL;
	return (semi);
}

t_semi		*ft_lstlastsemi(t_semi *semi)
{
	if (!semi)
		return (NULL);
	while (semi->next)
		semi = semi->next;
	return (semi);
}

void		lstadd_back_semi(t_gbl *gbl, char *str)
{
	if (gbl->semi != NULL)
		ft_lstlastsemi(gbl->semi)->next = ft_lstnewsemi(gbl, str);
	else
		gbl->semi = ft_lstnewsemi(gbl, str);
}
