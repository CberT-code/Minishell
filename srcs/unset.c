/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/26 10:55:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		delete_var(char *var, t_env *env)
{
	t_env	*env_n;

	env_n = env;
	while (env != NULL)
	{
		if ((ft_strlen((env)->var) == ft_strlen(var) &&
					ft_strcmp((env)->var, var) == 0) ||
				condition((env)->var, var))
		{
			suppr_maillon(&env_n, env);
			env = env_n;
			return (1);
		}
		env = (env)->next;
	}
	env = env_n;
	return (0);
}

void	unset(char *str, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i])
	{
		var = check_var(str);
		i += ft_strlen(var);
		if (str[i - 1] != '=')
			delete_var(var, env);
		i++;
	}
}

int		ft_unset(t_args *args, t_env *env)
{
	t_args	*first_arg;

	first_arg = args;
	while (args != NULL)
	{
		unset(args->str, env);
		args = args->next;
	}
	args = first_arg;
	return (1);
}
