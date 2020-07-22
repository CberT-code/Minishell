/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 17:25:15 by cbertola         ###   ########.fr       */
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
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipes;
		semicol->nb_cmd = i;
		semicol = semicol->next;
	}
	semicol = first_semicol;
	return (i);
}

void		new_str(t_semicol *semicol)
{
	t_args		*first_arg;
	t_pipes		*first_pipe;
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		first_pipe = semicol->pipes;
		while (semicol->pipes != NULL)
		{
			first_arg = semicol->pipes->cmds.args;
			if (semicol->pipes->cmds.args != NULL)
			{
				semicol->pipes->str = ft_strjoin_space(semicol->pipes->cmds.str, semicol->pipes->cmds.args->str);
				while (semicol->pipes->cmds.args->next != NULL)
				{
					semicol->pipes->cmds.args = semicol->pipes->cmds.args->next;
					semicol->pipes->str = ft_strjoin_space(semicol->pipes->str, semicol->pipes->cmds.args->str);
				}
			}
			else
				semicol->pipes->str = semicol->pipes->cmds.str;
			semicol->pipes->cmds.args = first_arg;
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipe;
		semicol = semicol->next;
	}
	semicol = first_semicol;
}

char		**new_tab(t_semicol *semicol)
{
	t_args		*first_arg;
	t_pipes		*first_pipe;
	t_semicol	*first_semicol;

	first_semicol = semicol;
	while (semicol != NULL)
	{
		first_pipe = semicol->pipes;
		while (semicol->pipes != NULL)
		{
			first_arg = semicol->pipes->cmds.args;
			if (semicol->pipes->cmds.args != NULL)
			{
				semicol->pipes->str = ft_strjoin_space(semicol->pipes->cmds.str, semicol->pipes->cmds.args->str);
				while (semicol->pipes->cmds.args->next != NULL)
				{
					semicol->pipes->cmds.args = semicol->pipes->cmds.args->next;
					semicol->pipes->str = ft_strjoin_space(semicol->pipes->str, semicol->pipes->cmds.args->str);
				}
			}
			else
				semicol->pipes->str = semicol->pipes->cmds.str;
			semicol->pipes->cmds.args = first_arg;
			semicol->pipes = semicol->pipes->next;
		}
		semicol->pipes = first_pipe;
		semicol = semicol->next;
	}
	semicol = first_semicol;
}