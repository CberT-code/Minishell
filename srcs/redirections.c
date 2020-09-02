/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:16:53 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/02 14:50:49 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_space_end(char *str, t_env *env, t_semicol *semicol)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		free_exit(semicol, env, ERROR_SYNTAX);
}

void	ft_redir_in(char *str, t_semicol *semicol, t_tab_redir *redir, t_env *env)
{
	while (*str)
	{
		if (*str == '<')
		{	
			if (*(++str) == '<')
			{
				check_space_end(str + 1, env, semicol);
				str++;
				str += *str == ' ' ? 1 : 0;
				lstadd_back_redir(&redir->doubl, ft_substr(str, 0,
				ft_strlen_str_quotes_backs(str, " ")), env);
			}
			else
			{
				check_space_end(str, env, semicol);
				str += *str == ' ' ? 1 : 0;
				lstadd_back_redir(&redir->simpl, ft_substr(str, 0,
				ft_strlen_str_quotes_backs(str, " ")), env);
			}
			str++;
			str += ft_strlen_str_quotes_backs(str, " ");
		}
		else
			str++;
	}
}
void	ft_redir_out(char *str, t_semicol *semicol, t_tab_redir *redir, t_env *env)
{
	while (*str)
	{
		if (*str == '>')
		{	
			if (*(++str) == '>')
			{
				check_space_end(str + 1, env, semicol);
				str++;
				str += *str == ' ' ? 1 : 0;
				lstadd_back_redir(&redir->doubl, ft_substr(str, 0,
				ft_strlen_str_quotes_backs(str, " ")), env);
			}
			else
			{
				check_space_end(str, env, semicol);
				str += *str == ' ' ? 1 : 0;
				lstadd_back_redir(&redir->simpl, ft_substr(str, 0,
				ft_strlen_str_quotes_backs(str, " ")), env);
			}
			str++;
			str += ft_strlen_str_quotes_backs(str, " ");
		}
		else
			str++;
	}
}
