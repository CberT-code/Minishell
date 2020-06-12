/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/06/12 11:45:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_lst_init_redir(t_redir *redir)
{
	redir->r_extern = NULL;
	redir->r_intern = NULL;
	redir->type_extern = NULL;
	redir->type_intern = NULL;
}

t_cmds			*ft_lstnewcmds(char *str)
{
	t_cmds *cmds;

	if (!(cmds = (t_cmds*)malloc(sizeof(t_cmds))))
		return (NULL);
	cmds->entry = str;
	cmds->pipes = split_minishell(str, '|');
	cmds->next = NULL;
	ft_lst_init_redir(&cmds->redir);
	return (cmds);
}

t_cmds			*ft_lstlast(t_cmds *cmds)
{
	if (!cmds)
		return (NULL);
	while (cmds->next)
		cmds = cmds->next;
	return (cmds);
}

void			ft_lstadd_back(t_cmds **alst, char *str)
{
	if (*alst != NULL)
		ft_lstlast(*alst)->next = ft_lstnewcmds(str);
	else
		*alst = ft_lstnewcmds(str);
}
