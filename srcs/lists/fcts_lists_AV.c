/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 14:45:41 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// static void		ft_lst_init_redir(t_redir *redir)
// {
// 	redir->r_out = NULL;
// 	redir->r_in = NULL;
// 	redir->type_out = NULL;
// 	redir->type_in = NULL;
// }

// t_cmds			*ft_lstnewcmds(char *str)
// {
// 	t_cmds *cmds;
// 	if (!(cmds = (t_cmds*)malloc(sizeof(t_cmds))))
// 		return (NULL);
// 	cmds->entry = str;
// 	cmds->pipes = split_minishell(str, '|');
// 	cmds->next = NULL;
// 	ft_lst_init_redir(&cmds->redir);
// 	return (cmds);
// }

// t_cmds			*ft_lstlast(t_cmds *cmds)
// {
// 	if (!cmds)
// 		return (NULL);
// 	while (cmds->next)
// 		cmds = cmds->next;
// 	return (cmds);
// }

// void			ft_lstadd_back(t_cmds **alst, char *str)
// {
// 	if (*alst != NULL)
// 		ft_lstlast(*alst)->next = ft_lstnewcmds(str);
// 	else
// 		*alst = ft_lstnewcmds(str);
// }