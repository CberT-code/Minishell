/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 20:38:37 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 18:01:50 by cbertola         ###   ########.fr       */
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
	while (nb_pipes--)
		close(pipes[nb_pipes]);
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
		if (param == 1)
			pipes[j * 2 + 1] = open(redir->str, O_RDONLY | O_WRONLY |
			O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		else
			pipes[j * 2 + 1] = open(redir->str, O_RDONLY | O_WRONLY | O_APPEND |
			O_CREAT, S_IRUSR | S_IWUSR);
		redir = redir->next;
	}
	redir = first_redir;
}

void	do_dup(int j, int *pipes, t_semi *semi, t_env *env)
{
	int		fd;
	t_redir	*first_redir;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	first_redir = semi->pipes->redir_in.simpl;
	while (semi->pipes->redir_in.simpl != NULL)
	{
		if ((fd = open(semi->pipes->redir_in.simpl->str, O_RDONLY)) < 0)
			return (free_exit(semi, env, ERROR_FILE_FOLDER));
		dup2(fd, 0);
		semi->pipes->redir_in.simpl = semi->pipes->redir_in.simpl->next;
	}
	semi->pipes->redir_in.simpl = first_redir;
	if (j < semi->nb_pipes - 1 || semi->pipes->redir_out.simpl != NULL
	|| semi->pipes->redir_out.doubl != NULL)
	{
		redir_out(semi->pipes->redir_out.simpl, 1, pipes, j);
		redir_out(semi->pipes->redir_out.doubl, 2, pipes, j);
		dup2(pipes[j * 2 + 1], 1);
	}
	close_pipes(semi->nb_pipes * 2 - 2, pipes);
}
