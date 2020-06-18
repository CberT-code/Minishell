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