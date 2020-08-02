/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/02 11:21:45 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int          delete_var(char *var, t_env **env)
{
    t_env   *env_n;

    env_n = *env;
    while (*env != NULL)
    {
        if ((ft_strlen((*env)->var) == ft_strlen(var) && 
        ft_strcmp((*env)->var, var) == 0) ||
        condition((*env)->var, var))
        {
            suppr_maillon(&env_n, *env);
            *env = env_n;
            return (1);
        }
        *env = (*env)->next;
    }
    *env = env_n;
    return (0);
}

void         unset(char *str, t_env **env)
{
    int     i;
    char    *var;

    i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\"' || str[i] == '\'')
            i++;
        var = check_var(str + i);
        i += ft_strlen(var);
        if (str[i - 1] != '=')
            delete_var(var, env);
        i++;
    }
}    

int         ft_unset(char *str, t_env **env, int fd)
{
    (void)fd;
    unset(str + 5, env);
    return (1);
}