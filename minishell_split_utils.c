#include "minishell.h"

int         ft_guillemets(char c, char c_b, char g)
{
    if (g == c && c_b != '\\')
		return (1);
	return (0);
}