/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 13:51:48 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		display_export_env(t_env *env)
{
	t_env	*start;

	start = env;
	while (env)
	{
		if (env->var[ft_strlen(env->var) - 1] == '=')
		{
			write(1, env->var, ft_strlen(env->var));
			if (env->valeur != NULL)
				write(1, env->valeur, ft_strlen(env->valeur));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	env = start;
	return (0);
}

int		ft_env(t_args *args, t_gbl *gbl)
{
	if (args == NULL)
		return (display_export_env(gbl->env));
	else
	{
		free_exit2(gbl, ERROR_FF);
		gbl->ret = 1;
	}
	return (1);
}
