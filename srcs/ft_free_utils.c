/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:32 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/02 15:05:11 by cbertola         ###   ########.fr       */
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

void	free_exit(t_semicol *semicol, t_env *env, char *str)
{
	t_semicol *first_semicol;

	if (semicol != NULL)
		first_semicol = semicol->first_semicol;
	else
		first_semicol = semicol;
	if (str != NULL)
		write(2, str, ft_strlen(str));
	if (first_semicol != NULL)
		ft_free(first_semicol);
	ft_free_env(env);
	exit(2);
}

void	ft_free_env(t_env *env)
{
	t_env *b_last;
	int i = 0;

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