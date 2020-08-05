/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 19:36:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_getenv(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(str, env->var, ft_strlen(str)) == 0
		&& ft_strncmp(str, env->var, ft_strlen(env->var)) == 0)
			return (env->valeur);
		env = env->next;
	}
	return (NULL);
}

int	ft_size_args(t_args *args)
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

int ft_cd(t_args **args, t_env *env)
{
	if (!*args || !(*args)->str
	|| ft_strncmp((*args)->str, "~", 1) == 0)
	{
		if (chdir(ft_getenv("HOME", env->var)) != 0)
		{
			ft_putendl("cd: Error - Environment variable $HOME not set");
			return (1);
		} 
		return (0); 
	}
	if (ft_size_args(*args) > 1)
	{
		ft_putendl("cd: Error - Too many arguments");
		return (1);
	}
	if (chdir((*args)->str) != 0)
	{
		ft_putendl("cd: Error - No such file or directory");
		return (1);
	}
	return (0);
}

/*
int main(int argc, char **arg, char **env)
{
	char cpy[1024];

	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	ft_cd("../", env);
	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	ft_cd("~", env);
	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	return (0);
}*/
