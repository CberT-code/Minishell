/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:24:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/04 11:41:17 by cbertola         ###   ########.fr       */
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

	if (!(env = (t_env*)ft_calloc(sizeof(t_env), 1)))
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

void			ft_shlvl(t_env *env)
{
	t_env	*first;
	int 	i;
	char 	*str;

	first = env;
	while (env)
	{
		if (ft_strcmp(env->var, "SHLVL=") == 0)
		{
			if ((i = ft_atoi(env->valeur)) < -1 || !ft_strisdigit(env->valeur + 1))
			{
				if (!ft_strisdigit(env->valeur + 1))
					str = ft_strdup("0");
				else
					str = ft_strdup("-1");
				free(env->valeur);
				env->valeur = str;
			}
			i = ft_atoi(env->valeur) + 1;
			free(env->valeur);
			env->valeur = ft_itoa(i);
		}
		env = env->next;
	}
	env = first;
}

void	ft_modif_shell(t_env *env)
{
	t_env *first_env;
	char cwd[1024];

	first_env = env;
	while(env)
	{
		if (strncmp(env->var, "SHELL=", ft_strlen(env->var)) == 0)
		{
			getcwd(cwd, 1024);
			ft_strdel(&env->valeur);
			env->valeur = ft_strjoin(cwd, "/minishell");
			return;		
		}
		env = env->next;
	}
	env = first_env;
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
	ft_shlvl(list);
	ft_modif_shell(list);
	return (list);
}
