/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 20:38:37 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/26 12:54:17 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pipes(int nb_pipes, int *pipes)
{
	int i;

	i = 0;
	while ((2 * i) < nb_pipes)
		pipe(pipes + (2 * i++));
}

void	close_pipes(int nb_pipes, int *pipes)
{
	int i;

	i = -1;
	while (++i < nb_pipes)
		close(pipes[i]);
}

void	wait_pipes(int nb_pipes, pid_t *pid, int *ret)
{
	int i;

	i = -1;
	while (++i < nb_pipes)
		waitpid(pid[i], ret, 0);
}

void	redir_out(t_redir *redir, int param, int *pipes, int j)
{
	t_redir		*first_redir;

	first_redir = redir;
	while (redir != NULL)
	{
		pipes[j * 2 + 1] = open(redir->str, param, S_IRUSR | S_IWUSR);
		redir = redir->next;
	}
	redir = first_redir;
}

void	do_dup(int j, int nb_pipes, int *pipes, t_pipes *pipe)
{
	int fd;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	while (pipe->redir_in.simpl != NULL)
	{
		if ((fd = open(pipe->redir_in.simpl->str, O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
		pipe->redir_in.simpl = pipe->redir_in.simpl->next;
	}
	if (j < nb_pipes - 1 || pipe->redir_out.simpl != NULL
	|| pipe->redir_out.doubl != NULL)
	{
		redir_out(pipe->redir_out.simpl, 1102, pipes, j);
		redir_out(pipe->redir_out.doubl, 2102, pipes, j);
		dup2(pipes[j * 2 + 1], 1);
	}
	close_pipes(nb_pipes * 2 - 2, pipes);
}
