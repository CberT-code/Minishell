/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/08/19 17:48:49 by user42           ###   ########.fr       */
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

void	ft_change_pwd(t_env *env)
{
	t_env	*env_cpy;
	char	cwd[1024];

	env_cpy = env;
	while (env_cpy && env_cpy->var && ft_strncmp(env_cpy->var, "PWD=", 4) != 0)
		env_cpy = env_cpy->next;
	getcwd(cwd, sizeof(cwd));
	if (env_cpy)
	{
		ft_strdel(&env_cpy->valeur);
		env_cpy->valeur = ft_strdup(cwd);
	}
	else
		ft_lstadd_back_env(&env, ft_strdup("PWD="), ft_strdup(cwd));
}

int		ft_oldpwd(t_env *env)
{
	t_env	*env_cpy;
	char	cwd[1024];
	env_cpy = env;
	while (env_cpy && env_cpy->var && ft_strncmp(env_cpy->var, "OLDPWD=", 7) != 0)
		env_cpy = env_cpy->next;
	getcwd(cwd, sizeof(cwd));
	if (chdir(env_cpy->valeur) != 0)
	{
		ft_putendl("cd: Error - No such file or directory");
		return (1);
	}
	else
	{
		ft_printf("%s\n", env_cpy->valeur);
		if (env_cpy)
		{
			ft_strdel(&env_cpy->valeur);
			env_cpy->valeur = ft_strdup(cwd);
		}
		else
			ft_lstadd_back_env(&env, ft_strdup("OLDPWD="), ft_strdup(cwd));
	}
	return(0);
}

int		ft_cd(t_args *args, t_env *env)
{
	t_env *env_cpy;
	char	cwd[1024];

	env_cpy = env;
	if (!args || !args->str
	|| ft_strncmp(args->str, "~", 1) == 0)
		return (ft_check_cd_errors(env));
	if (ft_check_size_args_cd(args) != 0)
		return (1);
	if (ft_strncmp(args->str, "-", 1) == 0)
		return (ft_oldpwd(env));
	getcwd(cwd, sizeof(cwd));
	if (chdir(args->str) != 0)
	{
		ft_putendl("cd: Error - No such file or directory");
		return (1);
	}
	while (env_cpy && env_cpy->var && ft_strncmp(env_cpy->var, "OLDPWD=", 7) != 0)
		env_cpy = env_cpy->next;
	if (env_cpy)
	{
		ft_strdel(&env_cpy->valeur);
		env_cpy->valeur = ft_strdup(cwd);
	}
	else
		ft_lstadd_back_env(&env, ft_strdup("OLDPWD="), ft_strdup(cwd));
	ft_change_pwd(env);
	return (0);
}
