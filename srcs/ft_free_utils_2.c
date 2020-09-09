/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:32 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 17:39:55 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exit_back_int(t_semi *semi, t_gbl *gbl, char *str, int res)
{
	t_semi	*first_semi;

	if (semi != NULL)
		first_semi = semi->first_semi;
	else
		first_semi = semi;
	ft_printf("exit\n");
	if (str != NULL)
		write(2, str, ft_strlen(str));
	if (first_semi != NULL)
		ft_free(first_semi);
	ft_free_env(gbl->env);
	ft_strdel(&gbl->pwd);
	ft_strdel(&gbl->path);
	ft_strdel(&gbl->line);
	exit(res);
}

void	exit_back2(t_gbl *gbl, char *str)
{
	ft_printf("exit\n");
	if (str != NULL)
		write(2, str, ft_strlen(str));
	gbl->ret = 1;
	gbl->error = 1;
}
