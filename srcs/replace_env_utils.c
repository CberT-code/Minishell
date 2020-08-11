/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 13:44:51 by user42            #+#    #+#             */
/*   Updated: 2020/08/11 11:12:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_envlen(char *str, t_env *env, int *cpt)
{
	t_env	*env_cpy;
	int		i;

	env_cpy = env;
	i = 0;
	while (str[i] != '=' && str[i] != '#' && str[i] != '-'
			&& str[i] != BACKS && str[i])
		i++;
	while (env_cpy)
	{
		if (ft_strncmp(str, env_cpy->var, i) == 0
		&& ft_strncmp(env_cpy->var, str, ft_strlen(env_cpy->var) - 1) == 0)
		{
			*cpt = *cpt + ft_strlen(env_cpy->valeur);
			return (i);
		}
		env_cpy = env_cpy->next;
	}
	return (i);
}

void	ft_simpq_len(char *str, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
	{
		(*len)++;
		(*i)++;
	}
}

void	ft_doubleq_len(char *str, t_env *env, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 2 && str[*i])
	{
		if (*i > 0 && str[*i] == BACKS && ft_isbacks(str, (*i) - 1) == 1)
			(*i)++;
		if (str[*i] == '$' && ft_isbacks(str, (*i) - 1) == 0)
			(*i) += ft_envlen(&str[(*i) + 1], env, len);
		else
			(*len)++;
		(*i)++;
	}
}

int		ft_envcpylen(char *str, t_env *env)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
				|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_len(str, &i, &len);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
				|| (i == 0 && str[i] == DOUBQ))
			ft_doubleq_len(str, env, &i, &len);
		else if ((i == 0 && str[i] == '$') || (i > 0 && str[i] == '$'
					&& ft_isbacks(str, i - 1) == 0))
			i += ft_envlen(&str[i + 1], env, &len);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			len++;
		else if (str[i] != BACKS)
			len++;
	}
	return (len);
}

int		ft_len_replace_ret(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (i < ft_strlen(str) - 1 && str[i] == '$' && str[i + 1] == '?')
		{
			len += ft_strlen(ft_itoa(g_ret));
			i++;
		}
		else
			len++;
	}
	return (len);
}

void	ft_fill_replace_ret(char **cpy, int *j, int *i)
{
	int k;
	char *cpy_ret;

	k = 0;
	cpy_ret = ft_strdup(ft_itoa(g_ret));
	while (cpy_ret[k])
		*cpy[(*j)++] = cpy_ret[k++];
	(*i)++;
	ft_strdel(&cpy_ret);
}

char	*ft_replace_ret(char *str)
{
	char	*cpy;
	int		i;
	int		j;
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_len_replace_ret(str) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i < ft_strlen(str) - 1 && str[i] == '$' && str[i + 1] == '?')
			ft_fill_replace_ret(&cpy, &j, &i);
		else
			cpy[j++] = str[i];
		i++;
	}
	cpy[j] = '\0';
	//ft_strdel(&str);
	return (cpy);
}
