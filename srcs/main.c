/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/15 10:41:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_rep;
char		*g_line;
int			g_sta;
t_semicol	*g_first_semicol;

void		sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		g_rep = 130;
		g_sta = 1;
	}
	if (sig == SIGQUIT && (!g_line || (g_line
					&& ft_strlen(g_line) == 0)))
		ft_printf("\b\b  \b\b");
	else if (sig == SIGQUIT && g_line && ft_strlen(g_line) > 0)
	{
		ft_free(g_first_semicol);
		ft_printf("Quitter (core dumped)\n");
		kill(1, SIGINT);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_semicol	*semicol;
	t_env		*env;
	char		cwd[1024];

	g_rep = 0;
	g_ret = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (argc <= 0 || !argv[0])
		return (1);
	g_line = NULL;
	env = ft_tab_to_list(envp);
	ft_printf("\033[1;33m SOLCYMINISHELL ➜\033[0;0m\033[1;36m ~%s\033[0;0m$ ", getcwd(cwd, sizeof(cwd)));
	while (1)
	{
		if (get_next_line(0, &g_line) == 1)
		{
			check_line(g_line);
			semicol = NULL;
			split_semicol(g_line, &semicol, env);
			count_pipe(semicol);
			tab_all(semicol);
			new_str(semicol);
			exec_cmds(semicol, &env);
			ft_free(semicol);
			ft_printf("\033[1;33m SOLCYMINISHELL ➜\033[0;0m\033[1;36m ~%s\033[0;0m$ ", getcwd(cwd, sizeof(cwd)));
		}
		else if (ft_strlen(g_line) == 0)
			break ;
		else
			free(g_line);
	}
	ft_free_env(env);
	ft_printf("exit\n");
	return (0);
}