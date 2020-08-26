/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 10:09:42 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/26 18:07:48 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int        list_size(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);

}

char       **list_to_tab(t_env **env)
{
    char    **tab;
    int     i;
    t_env   **first_env;

    first_env = env;
    if (!(tab = malloc(sizeof(char *) * (list_size(*env) + 1))))
        return (NULL);
    i = 0;
    while (*env)
    {
        if ((*env)->valeur != NULL)
            tab[i] = ft_strjoin((*env)->var, (*env)->valeur);
        else
            tab[i] = ft_strdup((*env)->var);
        i++;
        *env = (*env)->next;
    }
    env = first_env;
    return (tab);
}
