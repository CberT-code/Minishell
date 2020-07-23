/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:38:57 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 16:39:00 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_simpq_cpy(char *str, char *cpy, int *i, int *j)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
		cpy[(*j)++] = str[(*i)++];
}

int	ft_varcpy(char *str, char *cpy, char **env, int *j)
{
	int i;
	int l;
	int k;

	i = 0;
	k = -1;
	while ((ft_isalpha(str[i]) == 1 || str[i] == '_') && str[i])
		i++;
	while (env[++k])
	{
		l = 0;
		while (env[k][l] != '=' && env[k][l])
			l++;
		if (ft_strncmp(str, env[k], i) == 0 && ft_strncmp(env[k], str, l) == 0)
		{
			while (env[k][++l])
				cpy[(*j)++] = env[k][l];
			return (i);
		}
	}
	return (i);
}

int		ft_doubleq_cpy(char *str, char *cpy, char **env, int *j)
{
	int i;

	i = 1;
	while (ft_isquote(str, i) != 2 && str[i])
	{
		if ((i > 0 && str[i] == BACKS && ft_isbacks(str, (i) - 1) == 1)
		|| (i < ft_strlen(str) - 1 && str[i + 1] == DOUBQ && ft_isbacks(str, i) == 1))
			(i)++;
		if (i < ft_strlen(str) - 1 && str[i] == '$' && str[i + 1] != ' '
		&& str[i + 1] != DOUBQ && ft_isbacks(str, i - 1) == 0)
			i += ft_varcpy(&str[i + 1], cpy, env, j);
		else
			cpy[(*j)++] = str[i];
		i++;
	}
	return (i);
}

void	ft_conditions_cpy(char *str, char *cpy, char **env, int *j)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_cpy(str, cpy, &i, j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			i += ft_doubleq_cpy(&str[i], &cpy[0], env, j);
		else if ((i == 0 && ft_strlen(str) > 1 && str[i] == '$'
		&& str[i + 1] != ' ') || (i > 0 && i < ft_strlen(str) - 1
		&& str[i] == '$' && str[i] + 1 != ' ' && ft_isbacks(str, i - 1) == 0))
			i += ft_varcpy(&str[i + 1], &cpy[0], env, j);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[(*j)++] = str[i];
		else if (str[i] != BACKS)
			cpy[(*j)++] = str[i];
	}
}

char	*ft_envcpy(char *str, char **env)
{
	int		j;
	char	*cpy;

	j = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_envcpylen(str, env) + 1))))
		return (NULL);
	ft_conditions_cpy(str, cpy, env, &j);
	cpy[j] = '\0';
	return (cpy);
}

// int		main(int argc, char **argv, char **env)
// {
// 	char	*str;
// 	int		fd;
// 	char	*cpy;

// 	str = NULL;
// 	fd = 0;
// 	get_next_line(fd, &str);
// 	close(fd);
// 	cpy = ft_envcpy(str, env);
// 	return (0);
// }
