#include "../minishell.h"

int             in_quotes(char *s, int i, int in)
{
    int     j;

    j = 0;
    in = 0;
    while (j <= i)
    {
        if (s[j] == '\'' || s[j] == '\"')
            in = in == 0 ? 1 : 0;
        j++;
    }
    return (in);
}

int		ft_in_quotes(char *str, int i)
{
	int quote;
	int dbquote;
	int j;
	int last;

	quote = 0;
	dbquote = 0;
	last = 0;
	j = -1;
	while (++j < i)
	{
		if (j >= 0 && str[j] == SIMPQ)
		{
			
			quote++;
			last = 1;
		}
		if (j >= 0 && str[j] == DOUBQ )
		{
			dbquote++;
			last = 2;
		}
	}
	if (quote % 2 != 0 || dbquote % 2 != 0)
		return(last);
	return(0);	
}

// int		main(int argc, char **argv, char **env)
// {
// 	char *str;
// 	int		fd;
// 	int		i;

// 	str = NULL;
// 	fd = 0;
// 	get_next_line(fd, &str);
// 	close(fd);
// 	i = ft_in_quotes(str, 5);
// 	printf("here we test -> %d\n", i);
// 	return (0);
// }