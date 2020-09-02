/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/09/02 11:29:31 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir			*ft_lstnewredir(char *str, t_env *env)
{
	t_redir *redir;
	(void)env;
	
	if (!(redir = (t_redir*)calloc(sizeof(t_redir), 1)))
		return (NULL);
	redir->str = str;
	printf("here we test -> %p\n", redir->str);
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
