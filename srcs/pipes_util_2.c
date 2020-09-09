/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 20:38:37 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 11:12:21 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		do_fork(int j, int *pipes, t_semi *semi, t_gbl *gbl)
{
	do_dup(j, pipes, semi, gbl);
	if (semi->pipes->cmds.str == NULL)
		free_exit(gbl->semi, gbl, NULL);
	exec_fork(semi, j, gbl);
}

void		exchange_ret(t_gbl *gbl)
{
	gbl->ret = gbl->ret == 256 ? 1 : gbl->ret;
	gbl->ret = gbl->ret == 65280 ? 127 : gbl->ret;
	gbl->ret = gbl->ret == 32512 ? 127 : gbl->ret;
}
