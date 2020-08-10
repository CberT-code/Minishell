/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/10 12:57:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int				count_pipe(t_semicol *semicol)
{
	t_semicol	*first_semicol;
	t_pipes		*first_pipes;
	int			i;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		first_pipes = semicol->pipes;
		i = 0;
		while (semicol->pipes != NULL)
		{
			i++;
			count_args(&semicol->pipes->cmds);
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipes;
		semicol->nb_pipes = i;
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (i);
}

void			count_args(t_cmds *cmd)
{
	t_args	*cpy_args;
	int		i;

	i = 0;
	cpy_args = cmd->args;
	while (cpy_args != NULL)
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

void			new_str(t_semicol *semicol)
{
	t_pipes		*first_pipe;
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		first_pipe = semicol->pipes;
		while (semicol->pipes)
		{
			new_str_utils(semicol->pipes);
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipe;
		semicol = semicol->next;
	}
	semicol = first_semicol;
}

char			**new_tab(t_pipes *pipes)
{
	int			i;
	char		**tab_cmds;
	t_args		*first_args;

	if (!(tab_cmds = (char**)calloc(sizeof(char*), pipes->cmds.nb_args + 2)))
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
		tab_cmds[i] = 0;
	}
	pipes->cmds.args = first_args;
	return (tab_cmds);
}

void			tab_all(t_semicol *semicol)
{
	int			i;
	t_semicol	*first_semicol;
	t_pipes		*first_pipe;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		i = 0;
		if (!(semicol->all = ft_calloc(sizeof(char **), semicol->nb_pipes + 1)))
			return ;
		first_pipe = semicol->pipes;
		while (semicol->pipes != NULL)
		{
			semicol->all[i++] = new_tab(semicol->pipes);
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipe;
		semicol = semicol->next;
	}
	semicol = first_semicol;
}
