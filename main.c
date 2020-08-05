/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/05 21:56:07 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_rep;
char	*g_line;
int		g_sta;

void	ft_prompt(void)
{
	//char *dir;

	//ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");

	//dir = "SOLCYMINISHELL  ➜ ";
	// if (g_rep != 2)
	//  	ft_printf((g_rep == 0 ? YEL "✦ "YEL "%s "RED"(%s) ➜ "WHI :
	//  	RED "✦ "YEL "%s "RED"(%s) ➜ "WHI), "MINISHELL", dir);
	//if (dir != NULL)
	//	free(dir);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		g_rep = 130;
		g_sta = 1;
		ft_prompt();
	}
	if (sig == SIGQUIT && (!g_line || (g_line
	&& ft_strlen(g_line) == 0)))
		ft_printf("\b\b  \b\b");
	else if (sig == SIGQUIT && g_line && ft_strlen(g_line) > 0)
	{
		ft_printf("Quitter (core dumped)\n");
		kill(1, SIGINT);
	}
}

int     main(int argc, char **argv, char **envp)
{
	t_semicol 	*semicol;
	t_env		*env;

	g_rep = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (argc <= 0 || !argv[0])
		return (1);
	g_line = NULL;
	env = ft_tab_to_list(envp);
	while (1)
	{
    	ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
		if (get_next_line(0, &g_line) == 1)
		{
			semicol = NULL;
			split_semicol(g_line, &semicol, env);
			count_pipe(semicol);
			tab_all(semicol);
			new_str(semicol);
			exec_cmds(semicol);
		}
		else if (ft_strlen(g_line) == 0)
			break ;
		else
				free(g_line);
		ft_free(semicol, env);
	}
	ft_printf("exit\n");
	return (0);
}
