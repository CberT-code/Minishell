/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/18 17:35:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_fcts(t_cmds *cmd, t_env **env)
{
	if (strcmp(cmd->str, "echo") == 0)
		return (ft_echo(cmd->args));
	else if (strcmp(cmd->str, "env") == 0)
		return (ft_env(cmd->args, env));
	else if (strcmp(cmd->str, "export") == 0)
		return (ft_export(cmd->args, env));
	else if (strcmp(cmd->str, "cd") == 0)
		return (ft_cd(cmd->args, *env));
	else if (strcmp(cmd->str, "pwd") == 0)
		return (ft_pwd(cmd->args));
	else if (strcmp(cmd->str, "unset") == 0)
		return (ft_unset(cmd->args, *env));
	else
		return (-1);
}

int		search_mybin(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else
		return (0);
}

char	*check_path(char *str, t_env *env)
{
	char		**tab;
	struct stat	buf;
	int			i;
	char		*path;

	i = -1;
	while (strcmp(env->var, "PATH=") != 0)
		env = env->next;
	tab = ft_split(env->valeur, ':');
	while (tab[++i])
	{
		path = ft_strjoin(tab[i], "/");
		path = ft_strjoin_free(path, str, 1);
		if (stat(path, &buf) == 0)
		{
			i = 0;
			while (tab[++i])
				free(tab[i]);
			free(tab);
			return (path);
		}
		free(path);
	}
	return (NULL);
}