/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:40:15 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 11:06:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*check_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		while (str[i] != '\0' && str[i] != '=')
		{
			if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
				return (NULL);
			i++;
		}
		return (ft_strcpyuntil(str, "="));
	}
	else
		return (NULL);
}

char		*check_value(char *str, int i)
{
	char	*ret;
	int		start;

	if (str[i] == '\"' || str[i] == '\'')
		i++;
	start = i;
	if (ft_in_quotes(str, i) != 0)
	{
		while (ft_in_quotes(str, i) != 0)
			i++;
		i -= start;
		i--;
		ret = ft_strncpy(str + start, i);
		return (ret);
	}
	if (str[i] != ' ')
		return (ft_strcpyuntil(str + i, " "));
	return (NULL);
}

int			condition(char *str, char *str2)
{
	if ((ft_strlen(str) - ft_strlen(str2)) == 1)
	{
		if (strncmp(str, str2, ft_strlen(str)) == 61 &&
				str[ft_strlen(str) - 1] == '=')
			return (1);
		else
			return (0);
	}
	return (0);
}

int			replace_env(t_env *env, char *var, char *value)
{
	t_env	*env_n;

	env_n = env;
	while (env != NULL)
	{
		if ((ft_strlen(env->var) == ft_strlen(var) &&
					ft_strcmp(env->var, var) == 0) ||
				(condition(env->var, var)) || condition(var, env->var))
		{
			free(var);
			free(env->valeur);
			env->valeur = value;
			env = env_n;
			return (1);
		}
		env = env->next;
	}
	env = env_n;
	return (0);
}

int			ft_export(t_args *args, t_gbl *gbl)
{
	t_args	*first_arg;

	first_arg = args;
	if (args == NULL || args->str[0] == '#')
		return (display_export(gbl->env));
	while (args != NULL)
	{
		data_list(args->str, gbl);
		args = args->next;
	}
	args = first_arg;
	return (gbl->ret);
}
