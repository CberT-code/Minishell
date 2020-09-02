/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:16:53 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/02 17:21:32 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_space_end(char *str, t_env *env, t_semi *semi)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		free_exit(semi, env, ERROR_SYNTAX);
}

int		ft_check_redirs(char *str, char redir)
{
	int i;
	
	i = 0;
	while (str[i] == redir && str[i])
		i++;
	return (i);
}

void	ft_redir_in(char *str, t_semi *semi, t_tab_redir *redir, t_env *env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && ft_isbacks(str, i - 1) == 0)
		{	
			if (ft_check_redirs(&str[++i], '<') > 0)
				free_exit(semi, env, ERROR_SYNTAX);
			else
			{
				check_space_end(&str[i], env, semi);
				str += str[i] == ' ' ? 1 : 0;
				lstadd_back_redir(&redir->simpl, ft_substr(&str[i], 0,
				ft_strlen_str_quotes_backs(&str[i], " ")), env);
			}
			i++;
			i += ft_strlen_str_quotes_backs(&str[i], " ");
		}
		else
			i++;
	}
}

int 	ft_simp_redir_out (char *str, t_semi *semi, t_tab_redir *redir, t_env *env)
{
	int i;

	i = 0;
	check_space_end(str, env, semi);
	i += str[i] == ' ' ? 1 : 0;
	lstadd_back_redir(&redir->simpl, ft_substr(&str[i], 0,
	ft_strlen_str_quotes_backs(&str[i], " ")), env);
	return (i);
}

int 	ft_doub_redir_out (char *str, t_semi *semi, t_tab_redir *redir, t_env *env)
{
	int i;

	i = 0;
	check_space_end(&str[i + 1], env, semi);
	i++;
	i += str[i] == ' ' ? 1 : 0;
	lstadd_back_redir(&redir->doubl, ft_substr(&str[i], 0,
	ft_strlen_str_quotes_backs(&str[i], " ")), env);
	return (i);
}

void	ft_redir_out(char *str, t_semi *semi, t_tab_redir *redir, t_env *env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && ft_isbacks(str, i - 1) == 0)
		{	
			if (ft_check_redirs(&str[++i], '>') == 1)
				i += ft_doub_redir_out(&str[i], semi, redir, env);
			else if (ft_check_redirs(&str[i], '>') > 1)
				free_exit(semi, env, ERROR_SYNTAX);
			else
				i += ft_simp_redir_out(&str[i], semi, redir, env);
			i++;
			i += ft_strlen_str_quotes_backs(&str[i], " ");
		}
		else
			i++;
	}
}