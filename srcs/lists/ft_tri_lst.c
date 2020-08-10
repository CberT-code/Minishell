/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:51:47 by user42            #+#    #+#             */
/*   Updated: 2020/08/10 12:51:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew_var(char *var, char *valeur)
{
	t_env	*lst;

	if (!(lst = (t_env*)calloc(sizeof(t_env), 1)))
		return (NULL);
	lst->var = var;
	lst->valeur = valeur;
	lst->next = NULL;
	return (lst);
}

t_env	*ft_lstlast_var(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_var(t_env **alst, char *var, char *valeur)
{
	if (*alst != NULL)
		ft_lstlast_var(*alst)->next = ft_lstnew_var(var, valeur);
	else
		*alst = ft_lstnew_var(var, valeur);
}

void	ft_tri_varlst(t_env **lst_env)
{
	t_env	*new_lst;
	t_env	*cpy_lst;
	char	*var;
	char	*valeur;

	new_lst = *lst_env;
	while (new_lst->next)
	{
		cpy_lst = new_lst;
		while (cpy_lst->next)
		{
			if (ft_strcmp(cpy_lst->var, cpy_lst->next->var) > 0)
			{
				var = ft_strdup(cpy_lst->var);
				valeur = ft_strdup(cpy_lst->valeur);
				cpy_lst->var = ft_strdup(cpy_lst->next->var);
				cpy_lst->valeur = ft_strdup(cpy_lst->next->valeur);
				cpy_lst->next->var = ft_strdup(var);
				cpy_lst->next->valeur = ft_strdup(valeur);
			}
			cpy_lst = cpy_lst->next;
		}
		new_lst = new_lst->next;
	}
}
