/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 23:03:00 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 10:41:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (1);
	}
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

int		ft_delete_path(char *cpy)
{
	int i;

	i = ft_strlen(cpy) - 1;
	while (i > 0 && cpy[i] != ':')
		i--;
	return (i + 1);
}

void	ft_change_path(t_gbl *gbl)
{
	t_env	*first_env;
	char	*cpy;
	char	cwd[1024];

	first_env = gbl->env;
	while (gbl->env)
	{
		if (strncmp(gbl->env->var, "PATH=", ft_strlen(gbl->env->var)) == 0)
		{
			getcwd(cwd, 1024);
			cpy = ft_strdup(gbl->env->valeur);
			ft_strdel(&gbl->env->valeur);
			gbl->env->valeur = ft_strndup(cpy, ft_delete_path(cpy));
			gbl->env->valeur = ft_strjoin_free(gbl->env->valeur, cwd, 1);
			ft_strdel(&cpy);
			break ;
		}
		gbl->env = gbl->env->next;
	}
	gbl->env = first_env;
}
