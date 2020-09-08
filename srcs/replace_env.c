/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:38:57 by user42            #+#    #+#             */
/*   Updated: 2020/09/08 14:02:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_simpq_cpy(char *str, char *cpy, int *i, int *j)
{
	(*i)++;
	while (str[*i] != SIMPQ && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

int		ft_find_size_arg(char *str)
{
	int i;

	i = 0;
	while (str[i] != '#' && str[i] != '-' && str[i] != '='
	&& str[i] != '+' && str[i] != '}' && str[i] != '.'
	&& str[i] != '/' && str[i] != ',' && str[i] != '%'
	&& str[i] != ']' && str[i] != ':' && str[i] != BACKS
	&& str[i] != DOUBQ && str[i] != SIMPQ && str[i] != ' '
	&& str[i] != '^' && ft_isdigit(str[i]) == 0 && str[i])
		i++;
	return (i);
}

int		ft_varcpy(char *str, char *cpy, t_env *env, int *j)
{
	t_env	*env_cpy;
	int		i;
	int		l;

	env_cpy = env;
	l = 0;
	i = ft_find_size_arg(str);
	i = (ft_isdigit(str[i]) == 1) ? i + 1 : i;
	while (env_cpy)
	{
		if (ft_strncmp(str, env_cpy->var, i) == 0
		&& ft_strncmp(env_cpy->var, str, ft_strlen(env_cpy->var) - 1) == 0)
		{
			while (env_cpy->valeur && env_cpy->valeur[l])
				cpy[(*j)++] = env_cpy->valeur[l++];
			return (i);
		}
		env_cpy = env_cpy->next;
	}
	return (i);
}

int		ft_doubleq_cpy(char *str, char *cpy, t_env *env, int *j)
{
	int i;

	i = 1;
	while (ft_isquote(str, i) != 2 && str[i])
	{
		if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& ft_isbacks(str, i - 1) == 0
		&& str[i + 1] != '#' && str[i + 1] != '-' && str[i + 1] != '='
		&& str[i + 1] != '+' && str[i + 1] != '}' && str[i + 1] != '.'
		&& str[i + 1] != '/' && str[i + 1] != ',' && str[i + 1] != '%'
		&& str[i + 1] != ']' && str[i + 1] != ':' && str[i + 1] != BACKS
		&& str[i + 1] != DOUBQ && str[i + 1] != ' ' && str[i + 1] != '^')
			i += ft_varcpy(&str[i + 1], &cpy[0], env, j);
		else if ((str[i] == DOUBQ && ft_isbacks(str, i - 1) == 1)
		|| (str[i] != BACKS && str[i] != DOUBQ)
		|| (i < ft_strlen(str) - 1 && str[i] == BACKS
		&& ft_isbacks(str, i - 1) == 0 && str[i + 1] != DOUBQ
		&& str[i + 1] != '$'))
			cpy[(*j)++] = str[i];
		i++;
	}
	return (i);
}

void	ft_conditions_cpy(char *str, char *cpy, t_env *env, int *j)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy(str, cpy, &i, j);
		else if (str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
			i += ft_doubleq_cpy(&str[i], &cpy[0], env, j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& ft_isbacks(str, i - 1) == 0
		&& str[i + 1] != '#' && str[i + 1] != '-' && str[i + 1] != '='
		&& str[i + 1] != '+' && str[i + 1] != '}' && str[i + 1] != '.'
		&& str[i + 1] != '/' && str[i + 1] != ',' && str[i + 1] != '%'
		&& str[i + 1] != ']' && str[i + 1] != ':' && str[i + 1] != BACKS
		&& str[i + 1] != ' ' && str[i + 1] != '^')
			i += ft_varcpy(&str[i + 1], &cpy[0], env, j);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[(*j)++] = str[i];
		else if (str[i] != BACKS)
			cpy[(*j)++] = str[i];
	}
}

char	*ft_envcpy(char *str, t_gbl *gbl)
{
	int		j;
	char	*cpy;
	int		ret;

	ret = 1;
	j = 0;
	if ((ret = ft_verif_commands(str)) == 0 ||
	(ret = ft_verif_crochets(str, gbl->env)) == 0
	|| ft_verif_paranthesis(str) == 0)
		return (NULL);
	str = ft_clean_brackets(str);
	str = ft_replace_value(str, gbl);
	str = ft_replace_value2(str, gbl);
	str = ft_replace_crochets(str);
	str = ft_replace_bashname(str, gbl->env);
	if (!(cpy = (char*)ft_calloc(sizeof(char), ft_envcpylen(str, gbl->env) + 1)))
		return (NULL);
	ft_conditions_cpy(str, cpy, gbl->env, &j);
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}
