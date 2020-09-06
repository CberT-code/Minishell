/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/06 14:20:51 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				find_fcts(t_cmds *cmd, t_gbl *gbl)
{

	if (strcmp(cmd->str, "echo") == 0)
		return (ft_echo(cmd->args, gbl));
	else if (strcmp(cmd->str, "env") == 0)
		return (ft_env(cmd->args, gbl));
	else if (strcmp(cmd->str, "export") == 0)
		return (ft_export(cmd->args, gbl));
	else if (strcmp(cmd->str, "cd") == 0)
		return (ft_cd(cmd->args, gbl));
	else if (strcmp(cmd->str, "pwd") == 0)
		return (ft_pwd());
	else if (strcmp(cmd->str, "unset") == 0)
		return (ft_unset(cmd->args, gbl));
	else if (strcmp(cmd->str, "exit") == 0)
	{
		ft_exit(cmd, gbl);
		free_exit(gbl->semi, gbl, NULL);
		return (1);
	}
	else
		return (-1);
}

int				search_mybin(char *str)
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
	else if (strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

static char		*find_path(char *str, t_gbl *gbl)
{
	char		**tab;
	struct stat	buf;
	int			i;
	char		*path;

	i = -1;
	while (strcmp(gbl->env->var, "PATH=") != 0)
		gbl->env = gbl->env->next;
	tab = ft_split(gbl->env->valeur, ':');
	while (tab[++i])
	{
		path = ft_strjoin(tab[i], "/");
		path = ft_strjoin_free(path, str, 1);
		if (stat(path, &buf) == 0)
		{
			free_tab(tab);
			return (path);
		}
		free(path);
	}
	free_tab(tab);
	path = ft_strjoin(gbl->pwd, str);
	if (stat(path, &buf) == 0)
		return (path);
	return (NULL);	
}

char			*check_path(char *str, t_gbl *gbl)
{
	if (ft_isfind(str, '/') != -1)
		return (str);
	else
		return (find_path(str, gbl));

	
}