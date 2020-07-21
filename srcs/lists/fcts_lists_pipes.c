/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_lists_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 15:01:10 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipes			*ft_lstnewpipes(char *str)
{
	t_pipes *pipes;
	if (!(pipes = (t_pipes*)malloc(sizeof(t_pipes))))
		return (NULL);
	pipes->redir = full_redir(str);
	//pipes->str = str;
	pipes->str = clean_redir(str, '<');
	pipes->str = clean_redir(pipes->str, '>');
	printf("\tpipes -> |%s|\n", pipes->str);

	pipes->cmds = cmds_args(pipes->str);
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

void			lstadd_back_pipes(t_pipes **pipes, char *str)
{
	if (*pipes != NULL)
		ft_lstlastpipes(*pipes)->next = ft_lstnewpipes(str);
	else
		*pipes = ft_lstnewpipes(str);
}