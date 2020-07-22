/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 18:15:56 by cbertola         ###   ########.fr       */
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

void		new_str(t_semicol *semicol)
{
	int i;
	int j;
	char		**tab_cmds;
	
	i = 0;
	if (!(tab_cmds = (char**)malloc(sizeof(char*) * (semicol->nb_cmd + 1))))
		return (NULL);
	while (i < semicol->nb_cmd )
	{
		j = 0;
		if (!(tab_cmds[i] = (char*)malloc(sizeof(char) * (semicol->pipes->cmds.nb_args + 2))))
			return (NULL);
		while (j < semicol->pipes->cmds.nb_args)
		{
			tab_cmds[i][j] = ft_strdup(semicol->pipes->cmds.args->str);
			semicol->pipes->cmds.args = semicol->pipes->cmds.args->next;
			j++;
		}
		semicol->pipes = semicol->pipes->next;
		i++;
	}
	semicol = first_semicol;
}
