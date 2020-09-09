/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:40:15 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 12:11:13 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_pwd(t_gbl *gbl)
{
	t_env	*env_cpy;
	char	cwd[1024];

	env_cpy = gbl->env;
	while (env_cpy && env_cpy->var && ft_strncmp(env_cpy->var, "PWD=", 4) != 0)
		env_cpy = env_cpy->next;
	getcwd(cwd, sizeof(cwd));
	if (env_cpy)
	{
		ft_strdel(&env_cpy->valeur);
		env_cpy->valeur = ft_strdup(cwd);
		ft_strdel(&gbl->pwd);
		gbl->pwd = ft_strdup(env_cpy->valeur);
	}
	else
		add_back_env(&gbl->env, ft_strdup("PWD="), ft_strdup(cwd), gbl);
}

int		ft_oldpwd(t_gbl *gbl)
{
	t_env	*env_cpy;
	char	cwd[1024];

	env_cpy = gbl->env;
	while (env_cpy && env_cpy->var
	&& ft_strncmp(env_cpy->var, "OLDPWD=", 7) != 0)
		env_cpy = env_cpy->next;
	getcwd(cwd, sizeof(cwd));
	if (chdir(env_cpy->valeur) != 0)
	{
		ft_putstr_fd(ERROR_FF, 2);
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
			add_back_env(&gbl->env, ft_strdup("OLDPWD="), ft_strdup(cwd), gbl);
	}
	return (0);
}

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
