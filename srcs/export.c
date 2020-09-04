/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:40:15 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 10:34:05 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*check_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0')
	{
		return (ft_strcpyuntil(str + i, "="));
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

void		suppr_maillon(t_env **list, t_env *ptr)
{
	t_env	*start;

	start = *list;
	if (*list == NULL)
	{
		*list = ptr->next;
		return ;
	}
	while (*list != NULL)
	{
		if ((*list)->next == ptr)
		{
			(*list)->next = ptr->next;
			ft_strdel(&ptr->var);
			ft_strdel(&ptr->valeur);
			free(ptr);
			*list = start;
			return ;
		}
		*list = (*list)->next;
	}
	*list = start;
}

int			ft_export(t_args *args, t_gbl *gbl)
{
	t_args	*first_arg;

	first_arg = args;
	if (args == NULL)
		return (display_export(gbl->env));
	while (args != NULL)
	{
		data_list(args->str, gbl);
		args = args->next;
	}
	args = first_arg;
	return (gbl->ret);
}
