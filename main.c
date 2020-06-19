#include "minishell.h"

int     main(int argc, char **argv, char **envp)
{
	t_cmds	*cmd;
	char	*line;
	int i;
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (get_next_line(0, &line) > 0)
	{
        cmd = split_pipes(line, envp);
        free(line);
	}
	free(line);
}
