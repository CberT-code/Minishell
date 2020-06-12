#include "minishell.h"

int     main(void)
{
	int	ret;
	char	*line;
    ft_printf("\033[1;32m SOLCYMINISHELL  ➜ \033[0;0m");
	while (get_next_line(0, &line) > 0)
	{
        split_pipes(line);
        free(line);
	}
	free(line);
}