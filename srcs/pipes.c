/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/18 17:37:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		condition_do_pipe(t_semicol *semicol, char *str)
{
	if (semicol->nb_pipes == 1 && semicol->pipes->redir_in.simpl == NULL &&
			semicol->pipes->redir_in.doubl == NULL
			&& semicol->pipes->redir_out.simpl == NULL &&
			semicol->pipes->redir_out.doubl == NULL && search_mybin(str))
		return (1);
	return (0);
}

void	exec_fork(t_semicol *semicol, int j, t_env **env, int *pipes)
{
	char	*path;

	do_dup(j, semicol->nb_pipes, pipes, semicol->pipes);
	close_pipes(semicol->nb_pipes * 2, pipes);
	if ((g_ret = find_fcts(&semicol->pipes->cmds, env)) != -1)
		exit(g_ret);
	else
	{
		if ((path = check_path(semicol->pipes->cmds.str, *env)) != NULL)
		{
			if ((g_ret = execvp(path, semicol->all[j])))
			{
				free(path);
				exit(g_ret);
			}
		}
		else
		{
			g_ret = 127;
			ft_printf(ERROR_FIND_CMD, semicol->pipes->cmds.str);
			exit(3);
		}
		free(path);
	}
}

void	do_pipe(t_semicol *semicol, int *ret, t_env **env)
{
	int			pipes[semicol->nb_pipes * 2 + 1];
	int			j;
	t_pipes		*first_pipes;
	pid_t		pid[semicol->nb_pipes + 1];

	j = -1;
	init_pipes(semicol->nb_pipes * 2, pipes);
	first_pipes = semicol->pipes;
	while (++j < semicol->nb_pipes)
	{
		if (condition_do_pipe(semicol, semicol->pipes->cmds.str))
			g_ret = find_fcts(&semicol->pipes->cmds, env);
		else
		{
			if (!(pid[j] = fork()))
				exec_fork(semicol, j, env, pipes);
			waitpid(pid[j], ret, 0);
		}
		semicol->pipes = semicol->pipes->next;
	}
	semicol->pipes = first_pipes;
	close_pipes(semicol->nb_pipes * 2, pipes);
	wait_pipes(semicol->nb_pipes * 2, pid, ret);
}

int		exec_cmds(t_semicol *semicol, t_env **env)
{
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		do_pipe(semicol, &g_ret, env);
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (0);
}
