/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_brackets2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:50:14 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 22:55:09 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_iscrochet(char *str, int i)
{
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == ']')
		return (1);
	return (0);
}

int		ft_verif_word(char *str, t_env *env, t_gbl *gbl)
{
	t_env *first_env;

	first_env = env;
	while (env)
	{
		if (ft_strncmp(str, env->var, ft_strlen(str)) == 0
		&& ft_strncmp(env->var, str, ft_strlen(env->var) - 1) == 0)
		{
			free_exit2(gbl, "erreur de syntaxe : opérande attendu.");
			ft_strdel(&str);
			return (-1);
		}
		env = env->next;
	}
	env = first_env;
	ft_strdel(&str);
	return (1);
}

int		ft_travel_crochets(char *str, t_env *env, t_gbl *gbl)
{
	int		i;
	char	*cpy;

	i = 1;
	while (ft_iscrochet(str, i) != 1 && str[i])
	{
		if (ft_isdigit(str[i]) == 0 && ft_isalpha(str[i]) == 0)
		{
			free_exit2(gbl, "Caractère incorrect entre crochets.");
			return (-1);
		}
		i++;
	}
	if (str[i] != ']')
	{
		free_exit2(gbl, "Crochet manquant.");
		return (-1);
	}
	cpy = ft_strndup(&str[1], i - 1);
	if (ft_verif_word(cpy, env, gbl) == -1)
		return (-1);
	return (i);
}

void	ft_travel_simpq(char *str, int *i)
{
	if (str[*i] == SIMPQ && ft_isbacks(str, *i - 1) == 0)
	{
		(*i)++;
		while (ft_isquote(str, *i) != 1 && str[*i])
			(*i)++;
	}
}

int		ft_verif_crochets(char *str, t_env *env, t_gbl *gbl)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	while (str[++i])
	{
		ft_travel_simpq(str, &i);
		if (i > 0 && str[i] == '['
		&& str[i - 1] == '$' && ft_isbacks(str, i - 2) == 0)
			ret = ft_travel_crochets(&str[i], env, gbl);
		if (ret == -1)
			return (0);
		i += ret;
	}
	return (1);
}
