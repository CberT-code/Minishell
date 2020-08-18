/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:32 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/18 17:35:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(t_args *args)
{
	t_args *b_last;

	b_last = args;
	while (args != NULL)
	{
		free(args->str);
		b_last = args;
		args = args->next;
		free(b_last);
	}
}

void	free_cmds(t_cmds *cmds)
{
	free(cmds->str);
	free_args(cmds->args);
}

void	free_exit(t_semicol *semicol, t_env *env, char *str, void *param)
{
	if (str != NULL && param != NULL)
		ft_printf(str, param);
	if (str != NULL && param == NULL)
		write(1, str, ft_strlen(str));
	if (semicol != NULL)
		ft_free(semicol);
	ft_free_env(env);
	exit(2);
}

void	ft_free_env(t_env *env)
{
	t_env *b_last;

	while (env != NULL)
	{
		free(env->var);
		free(env->valeur);
		b_last = env;
		env = env->next;
		free(b_last);
	}
}
