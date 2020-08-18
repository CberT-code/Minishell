/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/15 10:44:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			display_export(t_env *env)
{
	t_env	*start;

	start = env;
	if (env != NULL)
		ft_tri_varlst(&env);
	while (env != NULL)
	{
		if (env->var[ft_strlen(env->var) - 1] == '=')
		{
			write(1, "declare -x ", 11);
			write(1, env->var, ft_strlen(env->var));
			if (env->valeur != NULL)
			{
				write(1, "\"", 1);
				write(1, env->valeur, ft_strlen(env->valeur));
				write(1, "\"", 1);
			}
			if (env->valeur == NULL && env->var[ft_strlen(env->var)] == '=')
				write(1, "\"\"", 2);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	env = start;
	return (1);
}

int			ft_tablen(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

char		*double_char(char *str, char c)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && (str[i - 1] != c || i == 0))
		{
			ret = add_char(str, c, i);
			free(str);
			str = ret;
		}
		i++;
	}
	return (str);
}

char		**ft_tri_vartab(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (j < ft_tablen(tab) - 1)
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				temp = ft_strdup(tab[j]);
				tab[j] = ft_strdup(tab[j + 1]);
				tab[j + 1] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void		data_list(char *str, t_env **env)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = check_var(str + i);
	i += ft_strlen(var);
	if (str[--i] == '=')
	{
		if (!(check_str_alpha(var, ft_strlen(var) - 1)))
			return (free_exit(NULL, *env, IDERRONE, var));
		value = check_value(str, ++i);
		value = ft_strcpyfrom(str, "=");
		i += ft_strlen(value);
	}
	else
	{
		if (check_str_alpha(var, ft_strlen(var)) == 0)
			return (free_exit(NULL, *env, IDERRTWO, var));
		value = NULL;
	}
	if (replace_env(*env, var, value) == 0)
		ft_lstadd_back_env(env, var, value);
}