/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/04 13:12:40 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipes			*ft_lstnewpipes(char *str, t_env *env)
{
	t_pipes 	*pipes;
	
	if (!(pipes = (t_pipes*)malloc(sizeof(t_pipes))))
		return (NULL);
	ft_bzero(pipes, sizeof(t_pipes));
	printf("We are here new pipes -> |%p|\n", pipes);
	ft_splitting(str, '<', &pipes->redir_in , env);
	ft_splitting(str, '>', &pipes->redir_out , env);
	str = clean_redir(str, '<');
	str = clean_redir(str, '>');
	pipes->str = ft_clean_spaces(str);
	printf("here we have new pipes->str -> |%p|  |%s|\n", pipes->str, pipes->str);
	printf("here we test cmd -> %p\n", &pipes->cmds);
	cmds_args(&pipes->cmds, pipes->str, env);
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

void			lstadd_back_pipes(t_pipes **pipes, char *str, t_env *env)
{
	if (*pipes != NULL)
		ft_lstlastpipes(*pipes)->next = ft_lstnewpipes(str, env);
	else
		*pipes = ft_lstnewpipes(str, env);
}