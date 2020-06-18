#include "../minishell.h"

int            len_next_word(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] == ' ' && str[i])
        i++;
    while (str[i] != ' ' && str[i])
    {
        i++;
        j++;
    }
    return (j);
}

int             ft_redir(char *s, char c)
{
    int     nb_redir;
    int     i;
    int     in;

    i = 0;
    nb_redir = 0;

    while (s[i])
    {
        if (s[i] == c && s[i])
        {
            nb_redir++;
            i++;
        }
        if (s[i] == c && s[i])
            i++;
        while (s[i] && (s[i] != c || in))
            in = in_quotes(s, i++, in);
    }
    return (nb_redir);
}

static char	        **ft_free(char **tab, int i)
{
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static int             ft_len_words(char *s, char c, int i, int *type_redir)
{
    int     len;
    int     in;

    len = 0;
    *type_redir = 0;
        while (s[i] && (s[i] != c || in))
        {
            i++;
            in = in_quotes(s, i, in);
            len++;
        }
        if (s[i] == c && s[i])
        {
            i++;
            *type_redir += 1;
        }
        if (s[i] == c && s[i])
        {
            i++;
           *type_redir += 1;
        }
        // printf("type_redir = %d\n",*type_redir);
    return (len);
}

static char            **ft_splitting(char *s, char c, int nb_redir, int *type_redir)
{
    char    **tab;
    int     ind;
    int     i;
    int     j;
    int     len;

    if (!(tab = (char **)malloc(sizeof(char *) * (nb_redir + 1))))
		return (NULL);
    j = 0;
    ind = 0;
    while (nb_redir--)
    {
        i = 0;
        len = ft_len_words(s, c, ind, &type_redir[j]);
        ind += len + type_redir[j];
        len = len_next_word(s + ind);
        if (!(tab[j] = malloc(sizeof(char) * len + 1)))
            return (ft_free(tab, j));
        while (s[ind] == ' ')
            ind++;
        while (len--)
            tab[j][i++] = s[ind++];
        tab[j++][i] = '\0';
    }
    return (tab);
}

char			**split_chevron(char *s, char c, int *type_redir)
{
    int     nb_redir;

    if (!s)
        return (NULL);
    nb_redir = ft_redir(s, c);
    // printf("redir = %d\n", nb_redir);
    return (ft_splitting( s, c, nb_redir, type_redir));
 
}

//   int main(void)
//   {
// 	 char **tab;
// 	 int i = 0;
// 	 int j = 0;
// 	 char *str;
//      int *redir;

// 	 str = "gr \";f < > \" < text.c > test >> pa << p >> popo >li";
//         // printf("adress tableau redir = %p\n", &redir);
//     if (!(redir = malloc(sizeof(int) * (ft_redir(str, '>') + 1))))
// 	        return (-1);
// 	 tab = split_chevron(str, '>', redir);
//         // printf("adress tableau redir = %p\n", &redir);
// 	while (tab[i])
// 	{
//     	printf("i = %d && print = %s\n",i, tab[i]);
//         // printf("adress redir = %p\n", &redir[i]);
//         printf("j = %d && print = %d\n",i, redir[i]);
// 	    i++;
// 	}

//  }