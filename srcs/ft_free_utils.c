/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:32 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/06 16:30:14 by user42           ###   ########.fr       */
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

void	free_exit(t_semi *semi, t_gbl *gbl, char *str)
{
	t_semi	*first_semi;

	if (semi != NULL)
		first_semi = semi->first_semi;
	else
		first_semi = semi;
	if (str != NULL)
		write(2, str, ft_strlen(str));
	if (first_semi != NULL)
		ft_free(first_semi);
	ft_free_env(gbl->env);
	ft_strdel(&gbl->pwd);
	exit(2);
}

void	free_exit2(t_gbl *gbl, char *str)
{
	if (str != NULL)
		write(2, str, ft_strlen(str));
	gbl->ret = 0;
}

void	ft_free_env(t_env *env)
{
	t_env	*b_last;
	int		i;

	i = 0;
	while (env)
	{
		free(env->var);
		free(env->valeur);
		b_last = env;
		i++;
		env = env->next;
		free(b_last);
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
