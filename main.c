#include "libft/libft.h"

int     main(void)
{
     int	fd;
	int	ret;
	char	*line;

	fd = open("pipes.c", O_RDONLY);
	while ((ret = get_next_line(1, &line)) != 0)
	{
		printf("|%d|%s\n", ret, line);
        free(line);
	}
	printf("|%d| coucou test\n", ret);
	free(line);
		while (1);
}