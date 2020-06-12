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
        ft_print_tab(cmds->pipes);
        printf("\n");
        cmds = cmds->next;
    }
    return (cmds);  
}