/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:32 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/06 08:44:32 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_args(t_args *args)
{
    t_args *b_last;

    b_last = args;
    while (args != NULL)
    {
        free(args->str);
        b_last = args;
        args = args->next;
        free(b_last);
    }
}

void    free_cmds(t_cmds *cmds)
{
        free(cmds->str);
        free_args(cmds->args);
}

void    free_exit(t_semicol *semicol, t_env *env, char *str, void *param)
{
    if (str != NULL && param != NULL)
        ft_printf(str, param);
    if (str != NULL && param == NULL)
        write(1, str, ft_strlen(str));
    if (semicol != NULL && env != NULL)
        ft_free(semicol, env);
    exit(2);
}