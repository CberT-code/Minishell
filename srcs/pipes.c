/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 11:10:04 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			path_env(t_gbl *gbl)
{
	t_env *first;

	first = gbl->env;
	while (ft_strcmp(gbl->env->var, "PATH=") != 0 && gbl->env->next != NULL)
		gbl->env = gbl->env->next;
	if (ft_strcmp(gbl->env->var, "PATH=") != 0)
	{
		gbl->env = first;
		write(2, ERROR_FF, ft_strlen(ERROR_FF));
		gbl->ret = 1;
		return (0);
	}
	gbl->env = first;
	return (1);
}

int			cond(t_semi *semi, char *str)
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
		if ((path = check_path(semi->pipes->cmds.str, gbl)) != NULL)
		{
			tab = list_to_tab(gbl->env);
			gbl->ret = execve(path, semi->all[j], tab);
			free_tab(tab);
		}
		else
		{
			gbl->ret = 127;
			ft_strdel(&path);
			free_exit_int(semi, gbl, ERROR_CMD, gbl->ret);
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
	ft_bzero(pid, sizeof(pid_t) * nb_cmd);
	init_pipes(nb_cmd * 2 - 2, pipes);
	if (semi->pipes->cmds.str != NULL)
		ft_change_args(&semi->pipes->cmds, gbl);
	tab_all(semi);
	while (++j < nb_cmd)
	{
		if (semi->pipes->cmds.str != NULL && cond(semi, semi->pipes->cmds.str))
			gbl->ret = find_fcts(&semi->pipes->cmds, gbl);
		else if (path_env(gbl))
		{
			if (!(pid[j] = fork()))
				do_fork(j, pipes, semi, gbl);
		}
		semi->pipes = semi->pipes->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, &gbl->ret);
	exchange_ret(gbl);
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
