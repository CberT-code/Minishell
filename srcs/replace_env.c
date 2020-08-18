/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:38:57 by user42            #+#    #+#             */
/*   Updated: 2020/08/18 17:35:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_simpq_cpy(char *str, char *cpy, int *i, int *j)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

int		ft_varcpy(char *str, char *cpy, t_env *env, int *j)
{
	t_env	*env_cpy;
	int		i;
	int		l;

	env_cpy = env;
	i = 0;
	l = 0;
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
			&& str[i] != BACKS && str[i])
		i++;
	while (env_cpy)
	{
		if (ft_strncmp(str, env_cpy->var, i) == 0
				&& ft_strncmp(env_cpy->var, str,
				ft_strlen(env_cpy->var) - 1) == 0)
		{
			while (env_cpy->valeur[l])
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
		if ((i > 0 && str[i] == BACKS && ft_isbacks(str, (i) - 1) == 1)
				|| (i < ft_strlen(str) - 1
				&& str[i + 1] == DOUBQ && ft_isbacks(str, i) == 1))
			(i)++;
		if (i < ft_strlen(str) - 1 && str[i] == '$' && str[i + 1] != ' '
				&& str[i + 1] != DOUBQ && ft_isbacks(str, i - 1) == 0)
			i += ft_varcpy(&str[i + 1], cpy, env, j);
		else
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
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
				|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_cpy(str, cpy, &i, j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
				|| (i == 0 && str[i] == DOUBQ))
			i += ft_doubleq_cpy(&str[i], &cpy[0], env, j);
		else if ((i == 0 && ft_strlen(str) > 1 && str[i] == '$'
					&& str[i + 1] != ' ') || (i > 0 && i < ft_strlen(str) - 1
					&& str[i] == '$' && str[i] + 1 != ' '
					&& ft_isbacks(str, i - 1) == 0))
			i += ft_varcpy(&str[i + 1], &cpy[0], env, j);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[(*j)++] = str[i];
		else if (str[i] != BACKS)
			cpy[(*j)++] = str[i];
	}
}

char	*ft_envcpy(char *str, t_env *env)
{
	int		j;
	char	*cpy;

	j = 0;
	if (!(cpy = (char*)calloc(sizeof(char), ft_envcpylen(str, env) + 1)))
		return (NULL);
	str = ft_replace_ret(str);
	ft_conditions_cpy(str, cpy, env, &j);
	cpy[j] = '\0';
	
	return (cpy);
}
