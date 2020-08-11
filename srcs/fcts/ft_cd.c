/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/08/11 11:02:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(str, env->var, ft_strlen(str)) == 0
		&& ft_strncmp(str, env->var, ft_strlen(env->var) - 1) == 0)
			return (env->valeur);
		env = env->next;
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

void	ft_change_pwd(t_env *env)
{
	t_env	*env_cpy;
	char	cwd[1024];

	env_cpy = env;
	while (ft_strncmp(env_cpy->var, "PWD=", 4) != 0)
		env_cpy = env_cpy->next;
	getcwd(cwd, sizeof(cwd));
	ft_strdel(&env_cpy->valeur);
	env_cpy->valeur = ft_strdup(cwd);
}

int		ft_cd(t_args *args, t_env *env)
{
	if (!args || !args->str
	|| ft_strncmp(args->str, "~", 1) == 0)
	{
		if (chdir(ft_getenv("HOME=", env)) != 0)
		{
			ft_putendl("cd: Error - Environment variable $HOME not set");
			return (8);
		}
		return (0);
	}
	if (ft_size_args(args) > 1)
	{
		ft_putendl("cd: Error - Too many arguments");
		return (8);
	}
	if (chdir(args->str) != 0)
	{
		ft_putendl("cd: Error - No such file or directory");
		g_ret = 8;
		return (8);
	}
	else
		ft_change_pwd(env);
	return (0);
}
