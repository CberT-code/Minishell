/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 10:09:42 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/25 10:24:02 by cbertola         ###   ########.fr       */
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

char       **list_to_tab(t_env *env)
{
    char    **tab;
    int     i;

    if (!(tab = malloc(sizeof(char *) * (list_size(env) + 1))))
        return (NULL);
    i = 0;
    while (env)
    {
        tab[i] = ft_strjoin(env->var, env->valeur);
        i++;
        env = env->next;
    }
    return (tab);
}
