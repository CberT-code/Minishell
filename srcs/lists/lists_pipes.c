/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/06 19:18:54 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipes			*ft_lstnewpipes(char *str, t_env *env)
{
	t_pipes 	*pipes;
	char 		*str2;
	char 		*str3;
	
	str2 = ft_strdup(str);
	pipes = NULL;
	if (!(pipes = (t_pipes*)calloc(sizeof(t_pipes), 1)))
		return (NULL);
	ft_bzero(pipes, sizeof(t_pipes));
	ft_splitting(str2, '<', &pipes->redir_in , env);
	ft_splitting(str2, '>', &pipes->redir_out , env);
	str2 = clean_redir(str2, '<');
	str2 = clean_redir(str2, '>');
	str3 = ft_clean_spaces(str2);
	cmds_args(&pipes->cmds, str3, env);
	pipes->next = NULL;
	free(str2);
	free(str3);
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