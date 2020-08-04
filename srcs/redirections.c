/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:16:53 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 10:36:55 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void            ft_splitting(char *str, char c, t_tab_redir *redir, t_env *env)
{
    while (*str)
    {
        if (*str == c)
        {
            if (*(++str) == c)
            {
                str++;
                str += *str == ' ' ? 1 : 0 ;
                lstadd_back_redir(&redir->doubl, ft_substr(str, 0, ft_strlen_str_quotes(str, " ")), env);
            }
            else
            {
                str += *str == ' ' ? 1 : 0 ;
                lstadd_back_redir(&redir->simpl, ft_substr(str, 0, ft_strlen_str_quotes(str, " ")), env);
            }
            str++;
            str += ft_strlen_str_quotes(str, " ");
        }
        else
            str++;
    }
}

t_tab_redir			full_redir(char *str, char c, t_env *env)
{
    t_tab_redir    redir;

    ft_bzero(&redir, sizeof(t_tab_redir));
    if (!str)
        return (redir);
    ft_splitting(str, c, &redir, env);
    return (redir);
 
}