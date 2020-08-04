/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_lists_args copy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 15:49:11 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_args			*ft_lstnewargs(char *str, t_env *env)
{
	t_args *args;

	if (!(args = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	printf("here we test args -> %p\n", args);
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