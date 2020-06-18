#include "../minishell.h"

char        *ft_cut_in_word(int start, int lenght, char *str)
{
    char    *str_cut;
    int     i;
    int     j;

    i = -1;
    if (!(str_cut = malloc(sizeof(char) * (ft_strlen(str) - lenght + 1))))
        exit(0);
    while (++i < start)
        str_cut[i] = str[i];
    j = i;
    while (lenght--)
        i++;
    while (str[i])
        str_cut[j++] = str[++i];
    str_cut[j] = '\0';
    free(str);

    return (str_cut);

}

char        *ft_echap_redir(char *s, char c)
{
    int     i;
    int     in;
    int     start;
    int     lenght;

    i = 0;
    lenght = 0;

    while (s[i] && (s[i] != c || in))
        in = in_quotes(s, i++, in);
    start = i;
    if (s[i] == '\0')
        return (s);
    while ((s[i] == c || s[i] == ' ' ) && s[i])
    {
        i++;
        lenght++;
    }
    if (s[i] == '\0')
        return (ft_strncpy_free(s, lenght));
    return (ft_cut_in_word(start, len_next_word(s + i) + lenght, s));
}

char    *clean_cmd(char *str)
{
    while (ft_redir(str, '<') != 0)
        str = ft_echap_redir(str, '<');
    while (ft_redir(str, '>') != 0)
        str = ft_echap_redir(str, '>');
    return (str);
}

// int         main(void)
// {
//     char *str;
//     char *test = "echo toto < bonjour pipou";

//     str = ft_strdup(test);
//     str = clean_cmd(str);
//     free(str);
// }
