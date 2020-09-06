/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/09/06 09:30:25 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir			*ft_lstnewredir(char *str, int i)
{
	t_redir *redir;

	if (!(redir = (t_redir*)ft_calloc(sizeof(t_redir), 1)))
		return (NULL);
	redir->str = str;
	redir->ind = i;
	redir->next = NULL;
	return (redir);
}

t_redir			*ft_lstlastredir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void			lstadd_back_redir(t_redir **redir, char *str, int i)
{
	if (*redir != NULL)
		ft_lstlastredir(*redir)->next = ft_lstnewredir(str, i);
	else
		*redir = ft_lstnewredir(str, i);
}
