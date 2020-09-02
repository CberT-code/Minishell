/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_semi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/08/31 11:59:58 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_semi	*ft_lstnewsemi(char *str, t_env *env)
{
	t_semi *semi;

	if (!(semi = (t_semi*)calloc(sizeof(t_semi), 1)))
		return (NULL);
	semi->str = str;
	semi->pipes = split_pipes(semi, env);
	semi->next = NULL;
	return (semi);
}

t_semi	*ft_lstlastsemi(t_semi *semi)
{
	if (!semi)
		return (NULL);
	while (semi->next)
		semi = semi->next;
	return (semi);
}

void		lstadd_back_semi(t_semi **semi, char *str, t_env *env)
{
	if (*semi != NULL)
		ft_lstlastsemi(*semi)->next = ft_lstnewsemi(str, env);
	else
		*semi = ft_lstnewsemi(str, env);
}
