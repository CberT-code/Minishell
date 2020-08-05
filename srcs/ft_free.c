/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:34:06 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/05 22:23:43 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_redir(t_redir *redir)
{
    t_redir *b_last;

    b_last = redir;
    while (redir != NULL)
    {
        free(redir->str);
        b_last = redir;
        redir = redir->next;
        free(b_last);
    }
}

void    free_tab_redir(t_tab_redir *redir)
{
    free_redir(redir->simpl);
    free_redir(redir->doubl);
}

void    free_pipes(t_pipes *pipes)
{
    t_pipes *b_last;

    b_last = pipes;
    while (pipes != NULL)
    {
        free(pipes->str);
        free_tab_redir(&pipes->redir_in);
        free_tab_redir(&pipes->redir_out);
        free_cmds(&pipes->cmds);
        b_last = pipes;
        pipes = pipes->next;
        free(b_last);
    }
}

void    free_tab_all(char ***all)
{
    int i;
    int j;

    i = 0;
    if (all)
    {
        while (all[i])
        {
            j = 0;
            while (all[i][j])
            {
                free(all[i][j]);
                j++;
            }
            free(all[i]);
            i++;
        }
        free(all);
    }
}

void    ft_free(t_semicol *semicol, t_env *env)
{
    void   *b_last;

    b_last = semicol;
    while (semicol != NULL)
    {
        free(semicol->str);
        free_tab_all(semicol->all);
        free_pipes(semicol->pipes);
        b_last = semicol;
        semicol = semicol->next;
        free(b_last);
    }
    while (env != NULL)
    {
        free(env->var);
        free(env->valeur);
        b_last = env;
        env = env->next;
        free(b_last);
    }
}