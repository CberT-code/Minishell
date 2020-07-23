/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:16:21 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipes			*ft_lstnewpipes(char *str, char **env)
{
	t_pipes *pipes;
	
	if (!(pipes = (t_pipes*)malloc(sizeof(t_pipes))))
		return (NULL);
	pipes->redir_in = full_redir(str, '<', env);
	pipes->redir_out = full_redir(str, '>', env);
	pipes->str = clean_redir(str, '<');
	pipes->str = clean_redir(pipes->str, '>');
	pipes->str = ft_clean_spaces(pipes->str);
	pipes->cmds = cmds_args(pipes->str, env);
	pipes->next = NULL;
	return (pipes);
}

t_pipes			*ft_lstlastpipes(t_pipes *pipes)
{
	if (!pipes)
		return (NULL);
	while (pipes->next)
		pipes = pipes->next;
	return (pipes);
}

void			lstadd_back_pipes(t_pipes **pipes, char *str, char **env)
{
	if (*pipes != NULL)
		ft_lstlastpipes(*pipes)->next = ft_lstnewpipes(str, env);
	else
		*pipes = ft_lstnewpipes(str, env);
}