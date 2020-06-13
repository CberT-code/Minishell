/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 09:55:46 by user42            #+#    #+#             */
/*   Updated: 2020/06/12 11:45:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_tab(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        printf("tab[%d] -> %s\n", i, tab[i]);
}

t_cmds     *split_pipes(char *str)
{
    t_cmds  *cmds;
    char    **tab;
    int     i;
    int     j;

    i = -1;
    cmds = NULL;
    tab = split_minishell(str, ';');
    while (tab[++i])
        ft_lstadd_back(&cmds, tab[i]);
    j = -1;
    while(cmds)
    {
        printf("entry -> %s\n", cmds->entry);
        //ft_print_tab(cmds->pipes);
        i = 0;
        while (cmds->pipes[i])
                i++;
        if (!(cmds->redir.type_in = (int **)malloc(sizeof(int *) * (i + 1))))
                return (NULL);
        if (!(cmds->redir.type_out = (int **)malloc(sizeof(int *) * (i + 1))))
                return (NULL);

        i = -1;
        while (cmds->pipes[++i])
        {
            printf("pipe = %s\n", cmds->pipes[i]);
            if (!(cmds->redir.type_out[i] = malloc(sizeof(int) * (ft_redir(cmds->pipes[i], '>') + 1))))
                return (NULL);
            if (!(cmds->redir.type_in[i] = malloc(sizeof(int) * (ft_redir(cmds->pipes[i], '<') + 1))))
                return (NULL);
            cmds->redir.r_out = split_chevron(cmds->pipes[i], '>', cmds->redir.type_out[i]);
            j = -1;
            while (cmds->redir.r_out[++j])
            printf("char_out = %s, type_out = %d\n\n", cmds->redir.r_out[j], cmds->redir.type_out[i][j]);
            cmds->redir.r_in = split_chevron(cmds->pipes[i], '<', cmds->redir.type_in[i]);
            j = -1;
            while (cmds->redir.r_in[++j])
            printf("char_out = %s, type_out = %d\n\n", cmds->redir.r_in[j], cmds->redir.type_in[i][j]);
        }
        printf("\n");
        cmds = cmds->next;
    }
    return (cmds);  
}