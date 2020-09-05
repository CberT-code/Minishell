/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:16:53 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/05 19:30:53 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_space_end(char *str, t_gbl *gbl)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		free_exit2(gbl, ERROR_SYNTAX);
}

int		ft_check_redirs(char *str, char redir)
{
	int i;
	
	i = 0;
	while (str[i] == redir && str[i])
		i++;
	return (i);
}

void	ft_redir_in(char *str, t_redir **redir, t_gbl *gbl)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && ft_isbacks(str, i - 1) == 0)
		{	
			if (ft_check_redirs(&str[++i], '<') > 0)
				free_exit2(gbl, ERROR_SYNTAX);
			else
			{
				check_space_end(&str[i], gbl);
				str += str[i] == ' ' ? 1 : 0;
				lstadd_back_redir(redir, ft_substr(&str[i], 0,
				ft_strlen_str_quotes_backs(&str[i], " ")), gbl->env, 1);
			}
			i++;
			i += ft_strlen_str_quotes_backs(&str[i], " ");
		}
		else
			i++;
	}
}

int 	ft_simp_redir_out (char *str, t_redir **redir, t_gbl *gbl)
{
	int i;

	i = 0;
	check_space_end(str, gbl);
	i += str[i] == ' ' ? 1 : 0;
	lstadd_back_redir(redir, ft_substr(&str[i], 0,
	ft_strlen_str_quotes_backs(&str[i], " ")), gbl->env, 1);
	return (i);
}

int 	ft_doub_redir_out (char *str, t_redir **redir, t_gbl *gbl)
{
	int i;

	i = 0;
	check_space_end(&str[i + 1], gbl);
	i++;
	i += str[i] == ' ' ? 1 : 0;
	lstadd_back_redir(redir, ft_substr(&str[i], 0,
	ft_strlen_str_quotes_backs(&str[i], " ")), gbl->env, 2);
	return (i);
}

void	ft_redir_out(char *str, t_redir **redir, t_gbl *gbl)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && ft_isbacks(str, i - 1) == 0)
		{	
			if (ft_check_redirs(&str[++i], '>') == 1)
				i += ft_doub_redir_out(&str[i], redir, gbl);
			else if (ft_check_redirs(&str[i], '>') > 1)
				free_exit2(gbl, ERROR_SYNTAX);
			else
				i += ft_simp_redir_out(&str[i], redir, gbl);
			i++;
			i += ft_strlen_str_quotes_backs(&str[i], " ");
		}
		else
			i++;
	}
}