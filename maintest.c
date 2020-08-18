#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int i;
	
	i = -1;
	while (env[++i])
		printf("env[i] -> %s\n", env[i]);
	return (0);
}