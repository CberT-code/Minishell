/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:52:35 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/25 15:02:36 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				split_semicol(char *str, t_semicol **semicol, t_env *env)
{
	int		start;
	char	*str2;
	char	*str3;

	start = 0;
	if (!str)
		return (0);
	str2 = ft_clean_spaces(str);
	while (str2[start])
	{
		str3 = ft_substr(str2 + start, 0,
		ft_strlen_str_quotes_backs(str2 + start, ";"));
		lstadd_back_semicol(semicol, str3, env);
		start += ft_strlen_str_quotes_backs(str2 + start, ";");
		if (str2[start] == ';')
			start++;

	}
	free(str2);
	return (1);
}

t_pipes			*split_pipes(char *str, t_env *env)
{
	t_pipes		*pipes;
	char		*str2;

	if (!str)
		return (NULL);
	pipes = NULL;
	while (*str)
	{
		str2 = ft_substr(str, 0, ft_strlen_str_quotes_backs(str, "|"));
		lstadd_back_pipes(&pipes, str2, env);
		str += ft_strlen_str_quotes_backs(str, "|");
		if (*str == '|')
			str++;
		free(str2);
	}
	return (pipes);
}

t_args			*split_args(char *str, t_env *env)
{
	t_args		*args;
	char		*str2;

	if (!str || *str == '\0')
		return (NULL);
	args = NULL;
	while (*str)
	{
		str2 = ft_substr(str, 0, ft_strlen_str_quotes(str, " "));
		lstadd_back_args(&args, str2, env);
		str += ft_strlen_str_quotes(str, " ");
		if (*str == ' ')
			str++;
		free(str2);
	}
	return (args);
}

void			cmds_args(t_cmds *cmd, char *str, t_env *env)
{
	while (*str == ' ')
		str++;
	cmd->str = ft_substr(str, 0, ft_strlen_str_quotes(str, " "));
	str += ft_strlen_str_quotes(str, " ") + 1;
	cmd->args = split_args(str, env);
}
