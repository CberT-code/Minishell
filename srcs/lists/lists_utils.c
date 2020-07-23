/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/23 17:16:22 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int				count_pipe(t_semicol *semicol)
{
	t_semicol	*first_semicol;
	t_pipes		*first_pipes;
	int i;

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
		semicol->nb_cmd = i;
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (i);
}

void			count_args(t_cmds *cmd)
{
	t_args	*cpy_args;
	int i;

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
	
	while (pipes != NULL)
	{
		first_arg = pipes->cmds.args;
		if (pipes->cmds.args != NULL)
		{
			pipes->str = ft_strjoin_space(pipes->cmds.str, pipes->cmds.args->str);
			while (pipes->cmds.args->next != NULL)
			{
				pipes->cmds.args = pipes->cmds.args->next;
				pipes->str = ft_strjoin_space(pipes->str, pipes->cmds.args->str);
			}
		}
		else
			pipes->str = pipes->cmds.str;
		pipes->cmds.args = first_arg;
		pipes = pipes->next;
	}
}

void		new_str(t_semicol *semicol)
{
	t_pipes		*first_pipe;
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		first_pipe = semicol->pipes;
		new_str_utils(semicol->pipes);
		semicol->pipes = first_pipe;
		semicol = semicol->next;
	}
	semicol = first_semicol;
}

void 		*new_tab(t_semicol *semicol)
{
	int			i;
	char		**tab_cmds;
	t_semicol	*first_semicol;

	i = 0;
	first_semicol = semicol;
	if (!(tab_cmds = (char**)malloc(sizeof(char*) * (first_semicol->pipes->cmds.nb_args + 2))))
		return (NULL);
	while (i < first_semicol->pipes->cmds.nb_args + 1 )
	{
		if (i == 0)
			tab_cmds[i] = ft_strdup(first_semicol->pipes->cmds.str);
		else
		{
			tab_cmds[i] = ft_strdup(first_semicol->pipes->cmds.args->str);
			first_semicol->pipes->cmds.args = first_semicol->pipes->cmds.args->next;
		}
		i++;
	}
	return (tab_cmds);
}

void	tab_all(t_semicol *semicol)
{	
	int 		i;
	t_semicol 	*first_semicol;

	first_semicol = semicol;
	i = -1;
	while (semicol != NULL)
	{
		if (!(semicol->all = malloc(sizeof(void *) * semicol->nb_cmd + 1)))
			return ;
		while (++i < semicol->nb_cmd)
		{
			semicol->all[i] = new_tab(semicol);
		}
		semicol = semicol->next;
	}
	semicol = first_semicol;
}

// void	ft_fill_cmds(t_semicol *semicol)
// {
// 	char **tab_cmds;
// 	t_semicol *first_semicol;
// 	int i;

// 	tab_cmds = new_tab(semicol);
// 	first_semicol = semicol;
// 	i = -1;
// 	if (!(first_semicol->all = (char***)malloc(sizeof(char**) * (ft_tablen(tab_cmds) + 1))))
// 		return;
// 	while (tab_cmds[++i])
// 		first_semicol->all[i] = tab_cmds[i];
// 	semicol = first_semicol;
	
// }


