/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:34:06 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 18:41:08 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir *b_last;

	b_last = redir;
	while (redir != NULL)
	{
		free(redir->str);
		b_last = redir;
		free(b_last);
		redir = redir->next;
	}
}

void	free_pipes(t_pipes *pipes)
{
	t_pipes *b_last;

	b_last = pipes;
	while (pipes != NULL)
	{
		free(pipes->str);
		free_redir(pipes->redir_in);
		free_redir(pipes->redir_out);
		free_cmds(&pipes->cmds);
		b_last = pipes;
		pipes = pipes->next;
		free(b_last);
	}
}

void	free_tab_all(char ***all)
{
	int i;
	int j;

	i = 0;
	if (all)
	{
		while (all[i])
		{
			j = 0;
			while (all[i][j])
			{
				free(all[i][j]);
				j++;
			}
			free(all[i]);
			i++;
		}
		free(all);
	}
}

void	ft_free(t_semi *semi)
{
	void	*b_last;

	b_last = semi;
	while (semi != NULL)
	{
		free(semi->str);
		free_tab_all(semi->all);
		free_pipes(semi->pipes);
		b_last = semi;
		semi = semi->next;
		free(b_last);
	}
}
