/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/02 17:21:32 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		condition_do_pipe(t_semi *semi, char *str)
{
	if (semi->nb_pipes == 1 && semi->pipes->redir_in.simpl == NULL &&
			semi->pipes->redir_in.doubl == NULL
			&& semi->pipes->redir_out.simpl == NULL &&
			semi->pipes->redir_out.doubl == NULL && search_mybin(str))
		return (1);
	return (0);
}

void		exec_fork(t_semi *semi, int j, t_env **env)
{
	char	*path;
	char	**tab;

	
	
	if ((g_ret = find_fcts(&semi->pipes->cmds, env, semi)) != -1)
		exit(g_ret);
	else
	{
		if ((path = check_path(semi->pipes->cmds.str, *env)) != NULL)
		{	
			g_ret = execve(path, semi->all[j], tab = list_to_tab(env));
			free_tab(tab);
		}
		else
		{
			g_ret = 127;
			free_exit(semi, *env, ERROR_FIND_CMD);
		}
		free(path);
		exit(g_ret);
	}
}

void	do_pipe(t_semi *semi, int nb_cmd, t_env **env)
{
	int			pipes[nb_cmd * 2 - 2];
	int			j;
	t_pipes		*first_pipes;
	pid_t		pid[nb_cmd];

	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	first_pipes = semi->pipes;
	ft_change_args(&semi->pipes->cmds, *env);
	tab_all(semi);
	while (++j < nb_cmd)
	{
		if (condition_do_pipe(semi, semi->pipes->cmds.str))
			g_ret = find_fcts(&semi->pipes->cmds, env, semi);
		else
		{
			if (!(pid[j] = fork()))
			{
				do_dup(j, pipes, semi, *env);
				exec_fork(semi, j, env);
			}
			//waitpid(pid[j], &g_ret, 0);
		}
		semi->pipes = semi->pipes->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, &g_ret);
	semi->pipes = first_pipes;
}

int		exec_cmds(t_semi *semi, t_env **env)
{
	t_semi	*first_semi;

	first_semi = semi;
	while (semi != NULL)
	{
		do_pipe(semi, semi->nb_pipes, env);
		semi = semi->next;
	}
	semi = first_semi;
	return (0);
}
