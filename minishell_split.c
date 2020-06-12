#include "minishell.h"

static int		ft_find_c(char letter, char c)
{
	if (letter == c)
		return (1);
	return (0);
}

static int		ft_words(char *s, char c)
{
	int 		i;
	int 		nb_words;
	t_d_int		guillemets;

	if (!s)
		return 0;
	i = 0;
	ft_bzero(&guillemets, sizeof(t_d_int));
	nb_words = 0;
	while (s[i])
	{
		while (ft_find_c(s[i], c) == 1 && s[i])
			i++;
		if (s[i])
			nb_words++;
		while (ft_find_c(s[i], c) == 0 && s[i] &&
		(((guillemets.i += ft_guillemets(s[i], s[i - 1], '\'')) % 2) == 0) &&
		(((guillemets.j += ft_guillemets(s[i], s[i - 1], '\"')) % 2) == 0))
			i++;
	}
	return (nb_words);
}

static char		**ft_free(char **tab_words, int i)
{
	while (--i >= 0)
		free(tab_words[i]);
	free(tab_words);
	return (NULL);
}

static int		f_l(char *s, char c, int i)
{
	int count_l;

	count_l = 0;
	while (ft_find_c(s[i], c) == 0 && s[i++])
		count_l++;
	return (count_l);
}

char			**split_minishell(char const *s, char c)
{
	char	**tab_words;
	t_d_int		wa;
	t_d_int		ind;
	t_d_int		guillemets;

	ind.i = 0;
	ft_bzero(&guillemets, sizeof(t_d_int));
	ft_bzero(&wa, sizeof(t_d_int));
	wa.i = ft_words((char *)s, c);
	if (!(tab_words = (char **)malloc(sizeof(char *) * (wa.i + 1))))
		return (NULL);
	while (wa.i--)
	{
		ind.j = 0;
		while (ft_find_c(s[wa.j], c) == 1 && s[wa.j])
			wa.j++;
		if (!(tab_words[ind.i] = malloc(sizeof(char) * (f_l((char *)s, c, wa.j) + 1))))
			return (ft_free(tab_words, ind.i));
		while (ft_find_c(s[wa.j], c) == 0 && s[wa.j] &&
		(((guillemets.i += ft_guillemets(s[wa.j], s[ind.i - 1], '\'')) % 2) == 0) &&
		(((guillemets.j += ft_guillemets(s[wa.j], s[ind.i - 1], '\"')) % 2) == 0))
			tab_words[ind.i][ind.j++] = s[wa.j++];
		tab_words[ind.i++][ind.j] = '\0';
	}
	tab_words[ind.i] = 0;
	return (tab_words);
}
