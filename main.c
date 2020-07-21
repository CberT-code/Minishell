#include "minishell.h"

int     main(int argc, char **argv, char **envp)
{
	char	*line;
	int i;
	t_semicol *semicol;

    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (get_next_line(0, &line) > 0)
	{
        split_semicol(line, semicol);
        free(line);
	}
	free(line);
}
