#include "../minishell.h"

static int             ft_words(char *s, char c)
{
    int     nb_words;
    int     i;
    int     in;

    i = 0;
    nb_words = 0;

    while (s[i])
    {
        if (s[i] == c && s[i])
            i++;
        if (s[i])
            nb_words++;
        while (s[i] && (s[i] != c || in))
            in = in_quotes(s, i++, in);
    }
    return (nb_words);
}

static char		**ft_free(char **tab, int i)
{
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static int             ft_len_words(char *s, char c, int i)
{
    int     len;
    int     in;

    len = 0;

        if (s[i] == c && s[i])
            i++;
        if (s[i])
            len++;
        while (s[i] && (s[i] != c || in))
        {
            in = in_quotes(s, i++, in);
            len++;
        }
    return (len);
}

static char            **ft_splitting(char *s, char c, int nb_words)
{
    char    **tab;
    int     ind;
    int     i;
    int     j;
    int     len;

    if (!(tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
    j = 0;
    len = 0;
    ind = 0;
    while (nb_words--)
    {
        i = 0;
        len = ft_len_words(s, c, ind);
        if (!(tab[j] = malloc(sizeof(char) * len + 1)))
            return (ft_free(tab, j));
        while (--len){
             tab[j][i++] = s[ind++];
        }
        ind++;
        tab[j++][i] = '\0';
    }
    tab[j] = NULL;
    return (tab);
}

char			**split_minishell(char *s, char c)
{
    int     nb_words;

    if (!s)
        return (NULL);
    nb_words = ft_words(s, c);
    return (ft_splitting( s, c, nb_words));
 
}

//  int main(void)
//  {
// 	 char **tab;
// 	 int i = 0;
// 	 char *str;

// 	 str = "gr\";f | \" ; test | voili ; voila | voilou \" tout; nu \" ta ; pa";
// 	 tab = split_minishell(str, '|');
// 	while (tab[i])
// 	{
// 	printf("i = %d && print = %s\n",i, tab[i]);
// 	i++;
// 	}
//  }