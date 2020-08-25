/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:24:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/25 19:40:37 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env			*ft_lstlast_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

t_env			*ft_lstnew_env(char *str, char *str2)
{
	t_env	*env;

	if (!(env = (t_env*)calloc(sizeof(t_env), 1)))
		return (NULL);
	env->var = str;
	env->valeur = str2;
	env->next = NULL;
	return (env);
}

void			ft_lstadd_back_env(t_env **alst, char *str, char *str2)
{
	if (*alst != NULL)
		ft_lstlast_env(*alst)->next = ft_lstnew_env(str, str2);
	else
		*alst = ft_lstnew_env(str, str2);
}

void			ft_shlvl(t_env **env)
{
	t_env	*first;
	int 	i;
	char 	*str;

	first = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->var, "SHLVL=") == 0)
		{
			if ((i = ft_atoi((*env)->valeur)) < -1 || !ft_strisdigit((*env)->valeur + 1))
			{
				if (!ft_strisdigit((*env)->valeur + 1))
					str = ft_strdup("0");
				else
					str = ft_strdup("-1");
				free((*env)->valeur);
				(*env)->valeur = str;
			}
			i = ft_atoi((*env)->valeur) + 1;
			free((*env)->valeur);
			(*env)->valeur = ft_strdup(ft_itoa(i));
		}
		*env = (*env)->next;
	}
	*env = first;
}

t_env			*ft_tab_to_list(char **tri_selectif)
{
	t_env	*list;
	int		i;

	list = NULL;
	i = 0;
	while (tri_selectif[i])
	{
		ft_lstadd_back_env(&list, ft_strcpyuntil(tri_selectif[i], "="),
		ft_strcpyfrom(tri_selectif[i], "="));
		i++;
	}
	i = 0;
	ft_shlvl(&list);
	return (list);
}
