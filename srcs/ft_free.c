/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:34:06 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 17:21:17 by cbertola         ###   ########.fr       */
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
        //free(semicol->str);
        printf("We are here 1\n");
        free_tab_all(semicol->all);
        printf("We are here 2\n");
        free_pipes(semicol->pipes);
        printf("We are here 3\n");
        b_last = semicol;
        semicol = semicol->next;
        free(b_last);
        printf("We are here 4\n");
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