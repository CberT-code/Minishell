/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/09/06 19:18:07 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipes			*ft_lstnewpipes(t_gbl *gbl, char *str)
{
	t_pipes		*pipes;
	char		*str2;
	char		*str3;

	str2 = ft_strdup(str);
	if (!(pipes = (t_pipes*)ft_calloc(sizeof(t_pipes), 1)))
		return (NULL);
	ft_redir_in(str2, &pipes->redir_in, gbl);
	ft_redir_out(str2, &pipes->redir_out, gbl);
	str2 = clean_redir(str2, '<');
	str2 = clean_redir(str2, '>');
	str3 = ft_clean_spaces(str2);
	if (ft_strcmp(str3,"\0") == 0)
		ft_strdel(&str3);
	if (str3 != NULL)
		cmds_args(&pipes->cmds, str3, gbl->env);
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

void			lstadd_back_pipes(t_gbl *gbl, t_pipes **pipes, char *str)
{
	if (*pipes != NULL)
		ft_lstlastpipes(*pipes)->next = ft_lstnewpipes(gbl, str);
	else
		*pipes = ft_lstnewpipes(gbl, str);
}
