/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/02 16:49:24 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir			*ft_lstnewredir(char *str, t_env *env)
{
	t_redir *redir;
	
	if (!(redir = (t_redir*)malloc(sizeof(t_redir))))
		return (NULL);
	redir->str = ft_envcpy(str, env);
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

void			lstadd_back_redir(t_redir **redir, char *str, t_env *env)
{
	if (*redir != NULL)
		ft_lstlastredir(*redir)->next = ft_lstnewredir(str, env);
	else
		*redir = ft_lstnewredir(str, env);
}