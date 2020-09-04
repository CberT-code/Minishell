/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 17:19:44 by cbertola         ###   ########.fr       */
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

void		exec_fork(t_semi *semi, int j, t_gbl *gbl)
{
	char	*path;
	char	**tab;

	
	if ((gbl->ret = find_fcts(&semi->pipes->cmds, gbl)) != 0)
		exit(gbl->ret);
	else
	{
		if ((path = check_path(semi->pipes->cmds.str, gbl->env)) != NULL)
		{	
			printf("We are here\n");
			gbl->ret = execve(path, semi->all[j], tab = list_to_tab(gbl->env));
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

void	do_pipe(t_semi *semi, int nb_cmd, t_gbl *gbl)
{
	int			pipes[nb_cmd * 2 - 2];
	int			j;
	t_pipes		*first_pipes;
	pid_t		pid[nb_cmd];

	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	first_pipes = semi->pipes;
	ft_change_args(&semi->pipes->cmds, gbl->env);
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
	wait_pipes(nb_cmd, pid, &g_ret);
	semi->pipes = first_pipes;
}

int		exec_cmds(t_semi *semi, t_gbl *gbl)
{
	t_semi	*first_semi;

	first_semi = semi;
	while (semi != NULL)
	{
		do_pipe(semi, semi->nb_pipes, gbl);
		semi = semi->next;
	}
	semi = first_semi;
	return (0);
}
