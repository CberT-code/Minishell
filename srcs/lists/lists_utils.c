/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 14:14:12 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int			count_pipe(t_semicol *semicol)
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
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipes;
		semicol->nb_cmd = i;
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (i);
}

void	new_str(t_pipes *pipes)
{
	t_args		*first_arg;
	t_pipes		*first_pipe;

	first_pipe = pipes;
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
	pipes = first_pipe;
}