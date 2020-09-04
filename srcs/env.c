/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 10:21:04 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		display_export_env(t_env *env)
{
	t_env	*start;

	start = env;
	while (env != NULL)
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
	return (1);
}

int		ft_env(t_env *env)
{
	display_export_env(env);
	return (1);
}
