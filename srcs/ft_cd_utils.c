/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 23:03:00 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 11:09:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *str, t_env *env)
{
	t_env *env_cpy;

	env_cpy = env;
	while (env_cpy)
	{
		if (ft_strncmp(str, env_cpy->var, ft_strlen(str)) == 0
		&& ft_strncmp(str, env_cpy->var, ft_strlen(env_cpy->var) - 1) == 0)
			return (env_cpy->valeur);
		env_cpy = env_cpy->next;
	}
	return (NULL);
}

int		ft_size_args(t_args *args)
{
	int	cpt;

	if (!args)
		return (0);
	cpt = 0;
	while (args)
	{
		args = args->next;
		cpt++;
	}
	return (cpt);
}

int		ft_check_cd_errors(t_env *env)
{
	if (chdir(ft_getenv("HOME=", env)) != 0)
	{
		ft_putendl("bash: cd: « HOME » non défini");
		g_ret = 1;
		return (1);
	}
	g_ret = 0;
	return (0);
}

int		ft_check_size_args_cd(t_args *args)
{
	if (ft_size_args(args) > 1)
	{
		ft_putendl("bash: cd: trop d'arguments");
		return (1);
	}
	return (0);
}
