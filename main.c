/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:49:48 by cbertola          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/07/23 17:23:53 by cbertola         ###   ########.fr       */
=======
/*   Updated: 2020/08/04 20:49:53 by cbertola         ###   ########.fr       */
>>>>>>> cyrille
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int     main(int argc, char **argv, char **envp)
{
	char		*line;
	t_semicol 	*semicol;
	t_env		*env;

	if (argc <= 0 || !argv[0])
		return (1);
	line = NULL;
	semicol = NULL;
	env = ft_tab_to_list(envp);
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (1)
	{
<<<<<<< HEAD
        split_semicol(line, &semicol, env);
		count_pipe(semicol);
		new_str(semicol);
		tab_all(semicol);
		printf("EXEC_CMDS ->\n");
		exec_cmds(semicol);
		while (semicol != NULL)
=======
		if (get_next_line(0, &line) == 1)
>>>>>>> cyrille
		{
			printf("here we start\n");
			split_semicol(line, &semicol, env);
			printf("split_semicol\n");
			count_pipe(semicol);
			printf("count_pipe\n");
			tab_all(semicol);
			printf("tab_all\n");
			new_str(semicol);
			printf("new_str\n");
			//exec_cmds(semicol);
			free(line);
		}
		else if (ft_strlen(line) == 0)
			break ;
		else
			free(line);
	}
	free(line);
	ft_free(semicol, env);
	ft_printf("exit\n");
	return (0);
}
