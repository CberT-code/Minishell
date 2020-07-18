/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 09:55:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 13:53:05 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_print_tab(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        printf("tab[%d] -> %s\n", i, tab[i]);
}

t_cmds     *parsing(char *str, char **envp)
{
    t_cmds  *cmds;
    char    **tab;
    int     i;
    int     j;
    t_semicol     semicol;
    
    i = -1;
    cmds = NULL;
    tab = split_semicol(str, ';');
    while (tab[++i]){
        tab[i] = ft_clean_quotes(tab[i]);
        tab[i] = ft_clean_spaces(tab[i]);
        tab[i] = ft_envcpy(tab[i], envp);
        ft_lstadd_back(&cmds, tab[i]);
    }
    j = -1;
    while(cmds)
    {
        printf("entry -> %s\n", cmds->entry); //display for test
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
            printf("pipe = %s\n", cmds->pipes[i]); //display for test
            if (!(cmds->redir.type_out[i] = malloc(sizeof(int) * (ft_redir(cmds->pipes[i], '>') + 1))))
                return (NULL);
            if (!(cmds->redir.type_in[i] = malloc(sizeof(int) * (ft_redir(cmds->pipes[i], '<') + 1))))
                return (NULL);
            cmds->redir.r_out = split_chevron(cmds->pipes[i], '>', cmds->redir.type_out[i]);
            j = -1;
            while (cmds->redir.r_out[++j])
            printf("char_out = %s, type_out = %d\n\n", cmds->redir.r_out[j], cmds->redir.type_out[i][j]); //display for test
            cmds->redir.r_in = split_chevron(cmds->pipes[i], '<', cmds->redir.type_in[i]);
            j = -1; //display for test
            while (cmds->redir.r_in[++j])
            printf("char_out = %s, type_out = %d\n\n", cmds->redir.r_in[j], cmds->redir.type_in[i][j]); //display for test
        }
        printf("\n");
        cmds = cmds->next;
    }
    return (cmds);  
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     t_cmds *test;

//     test = parsing("je suis \' toto \' ", envp);
//     return (0);
// }

int		main(int argc, char **argv, char **envp)
{
	int		fd;
    char    *str;
    t_cmds *test;

    str = NULL;
	fd = 0;
	get_next_line(fd, &str);
    test = parsing(str, envp);
	close(fd);
	//ft_printf("after -> %s\n", cpy);
	return (0);
}