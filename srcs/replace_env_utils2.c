/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:21:09 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 19:51:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_replace_value(char *str, t_gbl *gbl)
{
	int		i;
	int		len;
	char	*cpy;

	i = -1;
	len = 0;
	cpy = NULL;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_len(str, &i, &len);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& (str[i + 1] == '?' || str[i + 1] == '$')
		&& ft_isbacks(str, i - 1) == 0)
		{
			cpy = (str[i + 1] == '?') ? ft_itoa(gbl->ret) : ft_itoa(gbl->pid - 1);
			len += ft_strlen(cpy);
			i++;
			ft_strdel(&cpy);
		}
		else
			len++;
	}
	return (len);
}

int		ft_fill_replace_value(char *cpy, int *j, char c, t_gbl *gbl)
{
	int		k;
	char	*cpy_ret;
	int		i;

	i = 0;
	k = 0;
	cpy_ret = (c == '?') ? ft_itoa(gbl->ret) : ft_itoa(gbl->pid - 1);
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	i++;
	ft_strdel(&cpy_ret);
	return (i);
}

char	*ft_replace_value(char *str, t_gbl *gbl)
{
	char	*cpy;
	int		i;
	int		j;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_len_replace_value(str, gbl) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '?' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value(&cpy[0], &j, '?',gbl);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '$' && ft_isbacks(str, i - 1) == 0)
			i += ft_fill_replace_value(&cpy[0], &j, '$', gbl);
		else
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}

int		ft_len_bashname(char *str, t_env *env)
{
	int		i;
	int		len;
	t_env	*first_env;

	i = -1;
	len = 0;
	first_env = env;
	while (str[++i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_len(str, &i, &len);
		else if (i < ft_strlen(str) - 1 && str[i] == '$' && (str[i + 1] == '0'
		|| str[i + 1] == '$') && ft_isbacks(str, i - 1) == 0)
		{
			while (env)
			{
				if (ft_strncmp(env->var, "SHELL=", ft_strlen(env->var)) == 0)
					len += ft_strlen(env->valeur);
				env = env->next;
			}
			i++;
		}
		else
			len++;
	}
	env = first_env;
	return (len);
}

void	ft_fill_replace_bashname(char *cpy, int *j, int *i, t_env *env)
{
	int		k;
	char	*cpy_ret;
	t_env	*first_env;

	k = 0;
	cpy_ret = NULL;
	first_env = env;
	while (env)
	{
		if (ft_strncmp(env->var, "SHELL=", ft_strlen(env->var)) == 0)
			cpy_ret = ft_strdup(env->valeur);
		env = env->next;
	}
	env = first_env;
	while (cpy_ret[k])
		cpy[(*j)++] = cpy_ret[k++];
	(*i)++;
	ft_strdel(&cpy_ret);
}

char	*ft_replace_bashname(char *str, t_env *env)
{
	char	*cpy;
	int		i;
	int		j;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_len_bashname(str, env) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
			ft_simpq_cpy_all(str, cpy, &i, &j);
		else if (i < ft_strlen(str) - 1 && str[i] == '$'
		&& str[i + 1] == '0' && ft_isbacks(str, i - 1) == 0)
			ft_fill_replace_bashname(&cpy[0], &j, &i, env);
		else
			cpy[j++] = str[i];
		i++;
	}
	cpy[j] = '\0';
	ft_strdel(&str);
	return (cpy);
}
