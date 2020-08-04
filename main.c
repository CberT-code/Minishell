/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/04 14:07:19 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int     main(int argc, char **argv, char **envp)
{
	char		*line;
	t_semicol 	*semicol;
	t_env		*env;
	t_env		*data;
	t_env		*start;

	if (argc <= 0 || !argv[0])
		return (1);
	line = NULL;
	semicol = NULL;
	data = NULL;
	env = ft_tab_to_list(envp);
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (1)
	{
		if (get_next_line(0, &line) == 1)
		{
			printf("here we start\n");
			split_semicol(line, &semicol, env);
			printf("split_semicol\n");
			count_pipe(semicol);
			printf("count_pipe\n");
			tab_all(semicol);
			printf("tab_all\n");
			printf("here we test ce qu'on choisi-> |%s|\n", semicol->all[1][0]);
			printf("here we test ce qu'on choisi-> |%p|\n", semicol->all[1][0]);
			//test
			ft_free(semicol, env);
			free(line);
			while (1)
			{}
			//test
			//ft_export(semicol->pipes->str, &env, 1);
			//ft_unset(semicol->pipes->str, &env, 1);
			new_str(semicol);
			printf("new_str\n");
			ft_free(semicol, env);
			printf("ft_free\n");
			start = env;
			env = start;
			//exec_cmds(semicol);
			// while (semicol != NULL)
			// {
			// 	printf("semicol -> |%s|\n", semicol->str);
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
			semicol = semicol->next;
			//free(line);
		}
		else if (ft_strlen(line) == 0)
			break ;
		else
			free(line);
	}
	free(line);
	ft_printf("exit\n");
	return (0);
}

// int		main(int argc, char **argv, char **env)
// {
// 	char *str;
// 	int		fd;
//     t_semicol   *semicol;

//     (void)argc;
//     (void)argv;
// 	str = NULL;
//     semicol = NULL;
// 	fd = 0;
// 	get_next_line(fd, &str);
// 	close(fd);
//     split_semicol(str, semicol, env);
// 	return (0);
// }