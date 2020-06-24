/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:24:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/06/24 18:57:08 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	t_env *env;
    
	if (!(env = (t_env*)malloc(sizeof(t_env))))
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

t_env        *ft_tab_to_list(char **tri_selectif)
{
    t_env   *list;
    int     i;

    // ft_bzero(list, sizeof(t_env));
    list = NULL;
    i = 0;
    while (tri_selectif[i])
    {
       ft_lstadd_back_env(&list, ft_strcpyuntil(tri_selectif[i], "="), ft_strcpyfrom(tri_selectif[i], " =") );
        i++;
    }
    return (list);
}

int     main(int argc, char **argv, char **tri_selectif)
{
    t_env *test;

    test = ft_tab_to_list(tri_selectif);
    while (test->next != NULL)
    {
        printf("%s\n", test->var);
        test = test->next;
    }
}