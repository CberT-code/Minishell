/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/23 17:23:53 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int     main(int argc, char **argv, char **envp)
{
	char		*line;
	t_semicol 	*semicol;
	char		**env;

    (void)argc;
    (void)argv;
	semicol = NULL;
	env = envp;
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (get_next_line(0, &line) > 0)
	{
        split_semicol(line, &semicol, env);
		count_pipe(semicol);
		new_str(semicol);
		tab_all(semicol);
		printf("EXEC_CMDS ->\n");
		exec_cmds(semicol);
		while (semicol != NULL)
		{
			printf("semicol -> |%s|\n", semicol->str);
			while (semicol->pipes)
			{
				printf("\tthe new commande -> |%s|\n", semicol->pipes->str);
				while ((semicol->pipes->redir_in).simpl != NULL)
				{
					printf("\t\tredir simple in -> |%s|\n", (semicol->pipes->redir_in).simpl->str);
					(semicol->pipes->redir_in).simpl = (semicol->pipes->redir_in).simpl->next;
				}
				while ((semicol->pipes->redir_in).doubl != NULL)
				{
					printf("\t\tredir double in -> |%s|\n", (semicol->pipes->redir_in).doubl->str);
					(semicol->pipes->redir_in).doubl = (semicol->pipes->redir_in).doubl->next;
				}
				while ((semicol->pipes->redir_out).simpl != NULL)
				{
					printf("\t\tredir simple out -> |%s|\n", (semicol->pipes->redir_out).simpl->str);
					(semicol->pipes->redir_out).simpl = (semicol->pipes->redir_out).simpl->next;
				}
				while ((semicol->pipes->redir_out).doubl != NULL)
				{
					printf("\t\tredir double out -> |%s|\n", (semicol->pipes->redir_out).doubl->str);
					(semicol->pipes->redir_out).doubl = (semicol->pipes->redir_out).doubl->next;
				}
				printf("\tcommande -> |%s|\n", semicol->pipes->cmds.str);
				printf("\t\tnb_args -> |%d|\n", semicol->pipes->cmds.nb_args);
				while (semicol->pipes->cmds.args != NULL)
				{
					printf("\t\targs -> |%s|\n", semicol->pipes->cmds.args->str);
					semicol->pipes->cmds.args = semicol->pipes->cmds.args->next;
				}
				semicol->pipes = semicol->pipes->next;
			}
			printf("Nombre de pipes = %d\n", semicol->nb_cmd);      
			semicol = semicol->next;
		}
        free(line);
	}
	free(line);
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