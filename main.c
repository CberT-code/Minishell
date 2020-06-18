#include "minishell.h"

int     main(void)
{
	t_cmds	*cmd;
	char	*line;
	int i;
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (get_next_line(0, &line) > 0)
	{
        cmd = split_pipes(line);
		while (cmd)
		{
			printf("entry = %s\n", cmd->entry);
			i = -1;
			while (cmd->pipes[++i])
				printf(" pipe = %s\n", cmd->pipes[i]);
			i = -1;
			while (cmd->redir.r_out[++i])
			{
				printf(" r_out = %s\n", cmd->redir.r_out[i]);
			//	printf(" r_out = %d\n", cmd->redir.type_out[i]);
			}
			i = -1;
			while (cmd->redir.r_in[++i])
			{
				printf(" r_out = %s\n", cmd->redir.r_in[i]);
			//	printf(" r_out = %d\n", cmd->redir.type_in[i]);
			}
		}
        free(line);
	}
	free(line);
}
