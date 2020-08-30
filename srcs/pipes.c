/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/30 11:43:38 by cbertola         ###   ########.fr       */
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
	char	**tab;

	do_dup(j, semicol->nb_pipes, pipes, semicol->pipes);
	tab_all(semicol, j);
	if ((g_ret = find_fcts(&semicol->pipes->cmds, env, semicol)) != -1)
		exit(g_ret);
	else
	{
		if ((path = check_path(semicol->pipes->cmds.str, *env)) != NULL)
		{	
			g_ret = execve(path, semicol->all[j], tab = list_to_tab(env));
			free_tab(tab);
		}
		else
		{
			g_ret = 127;
			ft_printf(ERROR_FIND_CMD, semicol->pipes->cmds.str);
		}
		free(path);
		exit(g_ret);
	}
}

void	do_pipe(t_semicol *semicol, t_env **env)
{
	int			pipes[semicol->nb_pipes * 2 - 2];
	int			j;
	t_pipes		*first_pipes;
	pid_t		pid[semicol->nb_pipes];

	j = -1;
	init_pipes(semicol->nb_pipes * 2 - 2, pipes);
	first_pipes = semicol->pipes;
	while (++j < semicol->nb_pipes)
	{
		ft_change_args(semicol->pipes->cmds.args, *env);
		if (condition_do_pipe(semicol, semicol->pipes->cmds.str))
			g_ret = find_fcts(&semicol->pipes->cmds, env, semicol);
		else
		{
			if (!(pid[j] = fork())){
				exec_fork(semicol, j, env, pipes);
			waitpid(pid[j], &g_ret, 0);
			}
		}
		semicol->pipes = semicol->pipes->next;
	}
	j = -1;
	close_pipes(semicol->nb_pipes * 2 - 2, pipes);
	wait_pipes(semicol->nb_pipes + 1, pid, &g_ret);
	semicol->pipes = first_pipes;
}

int		exec_cmds(t_semicol *semicol, t_env **env)
{
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		do_pipe(semicol, env);
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (0);
}
