/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/06 10:34:11 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			condition_do_pipe(t_semi *semi, char *str)
{
	if (semi->nb_pipes == 1 && semi->pipes->redir_in == NULL &&
		semi->pipes->redir_out == NULL && search_mybin(str))
		return (1);
	return (0);
}

void		exec_fork(t_semi *semi, int j, t_gbl *gbl)
{
	char	*path;
	char	**tab;

	if ((find_fcts(&semi->pipes->cmds, gbl)) != -1)
		exit(gbl->ret);
	else
	{
		if ((path = check_path(semi->pipes->cmds.str, gbl->env)) != NULL)
		{
			tab = list_to_tab(gbl->env);
			gbl->ret = execve(path, semi->all[j], tab);
			free_tab(tab);
		}
		else
		{
			gbl->ret = 127;
			free_exit(semi, gbl->env, ERROR_FIND_CMD);
		}
		free(path);
		exit(gbl->ret);
	}
}

void		do_pipe(t_semi *semi, int nb_cmd, t_gbl *gbl)
{
	int			pipes[nb_cmd * 2 - 2];
	int			j;
	pid_t		pid[nb_cmd];

	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	ft_change_args(&semi->pipes->cmds, gbl);
	tab_all(semi);
	while (++j < nb_cmd)
	{
		if (condition_do_pipe(semi, semi->pipes->cmds.str))
			gbl->ret = find_fcts(&semi->pipes->cmds, gbl);
		else
		{
			if (!(pid[j] = fork()))
			{
				do_dup(j, pipes, semi, gbl->env);
				exec_fork(semi, j, gbl);
			}
		}
		semi->pipes = semi->pipes->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, &gbl->ret);
}

int			exec_cmds(t_semi *semi, t_gbl *gbl)
{
	t_semi		*first_semi;
	t_pipes		*first_pipes;

	first_semi = semi;
	while (semi != NULL)
	{
		first_pipes = semi->pipes;
		do_pipe(semi, semi->nb_pipes, gbl);
		semi->pipes = first_pipes;
		semi = semi->next;
	}
	semi = first_semi;
	return (0);
}
