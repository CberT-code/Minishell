/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/15 10:42:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_args			*ft_lstnewargs(char *str, t_env *env)
{
	t_args *args;

	if (!(args = (t_args*)calloc(sizeof(t_args), 1)))
		return (NULL);
	args->str = ft_envcpy(str, env);
	args->next = NULL;
	return (args);
}

t_args			*ft_lstlastargs(t_args *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void			lstadd_back_args(t_args **args, char *str, t_env *env)
{
	if (*args != NULL)
		ft_lstlastargs(*args)->next = ft_lstnewargs(str, env);
	else
		*args = ft_lstnewargs(str, env);
}
