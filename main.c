/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/05 13:14:57 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_rep;
char	*line;
int		g_sta;

void	ft_prompt(void)
{
	//char *dir;

	ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");

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
	if (sig == SIGQUIT && (!line || (line
	&& ft_strlen(line) == 0)))
		ft_printf("\b\b  \b\b");
	else if (sig == SIGQUIT && line && ft_strlen(line) > 0)
	{
		ft_printf("Quitter (core dumped)\n");
		kill(1, SIGINT);
	}
}

int     main(int argc, char **argv, char **envp)
{
	//char		*line;
	t_semicol 	*semicol;
	t_env		*env;

	g_rep = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (argc <= 0 || !argv[0])
		return (1);
	line = NULL;
	semicol = NULL;
	env = ft_tab_to_list(envp);
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (1)
	{

		if (get_next_line(0, &line) == 1)
		{
			split_semicol(line, &semicol, env);
			count_pipe(semicol);
			tab_all(semicol);
			new_str(semicol);
			//exec_cmds(semicol);
			//free(line);
			// test = semicol;
			// while (semicol != NULL)
			// {
			// 	printf("semicol -> |%s|\n", semicol->str);
			// 	printf("here we test le ptr -> %p\n", semicol);
			// 	printf("\tnext -> |%p|\n", semicol->next);
			// 	printf("\tpoiteur pipes -> |%p|\n", semicol->pipes);
			// 	while (semicol->pipes)
			// 	{
			// 		printf("\tthe new commande -> |%s|\n", semicol->pipes->str);
			// 		while ((semicol->pipes->redir_in).simpl != NULL)
			// 		{
			// 			printf("\t\tredir simple in -> |%s|\n", (semicol->pipes->redir_in).simpl->str);
			// 			(semicol->pipes->redir_in).simpl = (semicol->pipes->redir_in).simpl->next;
			// 		}
			// 		while ((semicol->pipes->redir_in).doubl != NULL)
			// 		{
			// 			printf("\t\tredir double in -> |%s|\n", (semicol->pipes->redir_in).doubl->str);
			// 			(semicol->pipes->redir_in).doubl = (semicol->pipes->redir_in).doubl->next;
			// 		}
			// 		while ((semicol->pipes->redir_out).simpl != NULL)
			// 		{
			// 			printf("\t\tredir simple out -> |%s|\n", (semicol->pipes->redir_out).simpl->str);
			// 			(semicol->pipes->redir_out).simpl = (semicol->pipes->redir_out).simpl->next;
			// 		}
			// 		while ((semicol->pipes->redir_out).doubl != NULL)
			// 		{
			// 			printf("\t\tredir double out -> |%s|\n", (semicol->pipes->redir_out).doubl->str);
			// 			(semicol->pipes->redir_out).doubl = (semicol->pipes->redir_out).doubl->next;
			// 		}
			// 		printf("\tcommande -> |%s|\n", semicol->pipes->cmds.str);
			// 		printf("\t\tnb_args -> |%d|\n", semicol->pipes->cmds.nb_args);
			// 		while (semicol->pipes->cmds.args != NULL)
			// 		{
			// 			printf("\t\targs -> |%s|\n", semicol->pipes->cmds.args->str);
			// 			semicol->pipes->cmds.args = semicol->pipes->cmds.args->next;
			// 		}
			// 		semicol->pipes = semicol->pipes->next;
			// 	}
			// 	printf("Nombre de pipes = %d\n", semicol->nb_pipes);      
			// semicol = semicol->next;
			// }
			// semicol = test;
		}
		else if (ft_strlen(line) == 0)
		{
			printf("here we test elseif\n");
			break ;
		}
		else
				free(line);
	}
	ft_free(semicol, env);
	ft_printf("exit\n");
	return (0);
}
