/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/09/06 18:25:11 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				count_pipe(t_semi *semi)
{
	t_semi		*first_semi;
	t_pipes		*first_pipes;
	int			i;

	first_semi = semi;
	while (semi != NULL)
	{
		first_pipes = semi->pipes;
		i = 0;
		while (semi->pipes != NULL)
		{
			i++;
			count_args(&semi->pipes->cmds);
			semi->pipes = semi->pipes->next;
		}
		semi->pipes = first_pipes;
		semi->nb_pipes = i;
		semi = semi->next;
	}
	semi = first_semi;
	return (i);
}

void			count_args(t_cmds *cmd)
{
	t_args	*cpy_args;
	int		i;

	i = 0;
	cpy_args = cmd->args;
	while (cpy_args)
	{
		i++;
		cpy_args = cpy_args->next;
	}
	cmd->nb_args = i;
}

static void		new_str_utils(t_pipes *pipes)
{
	t_args		*first_arg;
	char		*str;

	first_arg = pipes->cmds.args;
	if (pipes->cmds.args != NULL)
	{
		str = ft_strdup(pipes->cmds.str);
		while (pipes->cmds.args != NULL)
		{
			pipes->str = ft_strjoin_space(str, pipes->cmds.args->str);
			free(str);
			str = pipes->str;
			pipes->cmds.args = pipes->cmds.args->next;
		}
	}
	else
		pipes->str = ft_strdup(pipes->cmds.str);
	pipes->cmds.args = first_arg;
}

void			new_str(t_semi *semi)
{
	t_pipes		*first_pipe;
	t_semi		*first_semi;

	first_semi = semi;
	while (semi != NULL)
	{
		first_pipe = semi->pipes;
		while (semi->pipes)
		{
			semi->first_semi = first_semi;
			if (semi->pipes->cmds.str != NULL)
				new_str_utils(semi->pipes);
			semi->pipes = semi->pipes->next;
		}
		semi->pipes = first_pipe;
		semi = semi->next;
	}
	semi = first_semi;
}

char			**new_tab(t_pipes *pipes)
{
	int			i;
	char		**tab_cmds;
	t_args		*first_args;

	if (!(tab_cmds = (char**)ft_calloc(sizeof(char*), pipes->cmds.nb_args + 2)))
		return (NULL);
	i = 0;
	first_args = pipes->cmds.args;
	while (i <= pipes->cmds.nb_args)
	{
		if (i == 0)
			tab_cmds[i] = ft_strdup(pipes->cmds.str);
		else
		{
			tab_cmds[i] = ft_strdup(pipes->cmds.args->str);
			pipes->cmds.args = pipes->cmds.args->next;
		}
		i++;
	}
	tab_cmds[i] = NULL;
	pipes->cmds.args = first_args;
	return (tab_cmds);
}

void			tab_all(t_semi *semi)
{
	t_pipes		*first_pipe;
	int			j;

	j = -1;
	if (!(semi->all = ft_calloc(sizeof(char **), semi->nb_pipes + 1)))
		return ;
	first_pipe = semi->pipes;
	while (semi->pipes)
	{
		if (semi->pipes->cmds.str != NULL)
			semi->all[++j] = new_tab(semi->pipes);
		semi->pipes = semi->pipes->next;
	}
	semi->pipes = first_pipe;
}
