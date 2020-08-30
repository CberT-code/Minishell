/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/08/29 22:25:58 by user42           ###   ########.fr       */
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
		ft_putendl("bash: cd: « OLDPWD » non défini");
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
	|| ft_strncmp(args->str, "~", ft_strlen(args->str)) == 0)
		return (ft_check_cd_errors(env));
	if (ft_check_size_args_cd(args) != 0)
	{
		g_ret = 1;
		return (1);
	}
	if (ft_strncmp(args->str, "-", 1) == 0)
		return (ft_oldpwd(env));
	if (args->str[0] == '~')
		args->str = ft_strjoin(ft_getenv("HOME", env), &args->str[1]);
	if (ft_strncmp(args->str, "$dir", 4) == 0)
	{
		ft_strdel(&args->str);
		args->str = ft_strdup(ft_getenv("HOME", env));
	}
	getcwd(cwd, sizeof(cwd));
	if (chdir(args->str) != 0)
	{
		g_ret = 1;
		ft_printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", args->str);
		return (1);
	}
	while (env_cpy && env_cpy->var && ft_strncmp(env_cpy->var, "OLDPWD=", 7) != 0)
		env_cpy = env_cpy->next;
	if (env_cpy)
	{
		ft_strdel(&env_cpy->valeur);
		env_cpy->valeur = ft_strdup(ft_getenv("PWD", env));
	}
	else
		ft_lstadd_back_env(&env, ft_strdup("OLDPWD="), ft_strdup(ft_getenv("PWD", env)));
	ft_change_pwd(env);
	g_ret = 0;
	return (0);
}
