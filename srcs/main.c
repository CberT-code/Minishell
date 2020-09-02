/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:50:03 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/02 17:36:41 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gbl	g_gbl;

void		sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		g_gbl.rep = 130;
		g_gbl.sta = 1;
	}
	if (sig == SIGQUIT && (!g_gbl.line || (g_gbl.line
					&& ft_strlen(g_gbl.line) == 0)))
		ft_printf("\b\b  \b\b");
	else if (sig == SIGQUIT && g_gbl.line && ft_strlen(g_gbl.line) > 0)
	{
		ft_free(g_gbl.semi);
		ft_printf("Quitter (core dumped)\n");
		kill(1, SIGINT);
	}
}

int		exec_line(t_gbl *gbl, t_semi *semi, t_env **env)
{
	(void)gbl;
	semi = NULL;
	split_semi(g_gbl.line, &semi, *env);
	count_pipe(semi);
	new_str(semi);
	exec_cmds(semi, env);
	ft_free(semi);
	g_gbl.line = NULL;
	//ft_printf("\033[1;33m SOLCYMINISHELL ➜\033[0;0m\033[1;36m ~%s\033[0;0m$ ", getcwd(cwd, sizeof(cwd)));
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env;
	//char		cwd[1024];

	ft_bzero(&g_gbl, sizeof(t_gbl));
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (argc <= 0 || !argv[0])
		return (1);
	g_gbl.line = NULL;
	env = ft_tab_to_list(envp);
	//ft_printf("\033[1;33m SOLCYMINISHELL ➜\033[0;0m\033[1;36m ~%s\033[0;0m$ ", getcwd(cwd, sizeof(cwd)));
	while (1)
	{
		if ((g_gbl.rep = get_next_line(0, &g_gbl.line)) == 1)
			exec_line(&g_gbl, g_gbl.semi, &env);
		else if (g_gbl.rep == -1)
			break ;
	}
	ft_free_env(env);
	//ft_printf("exit\n");
	return (0);
}
