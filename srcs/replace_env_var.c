/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:38:57 by user42            #+#    #+#             */
/*   Updated: 2020/07/20 18:15:14 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isbacks(char *str, int i)
{
	int cpt;

	cpt = 0;
	while (i >= 0 && str[i] == BACKS)
	{
		cpt++;
		i--;
	}
	if (cpt % 2 == 0)
		return (0);
	return (1);
}
 
int	ft_isquote(char *str, int i)
{

	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == DOUBQ)
		return (2);
	if (i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == SIMPQ)
		return (1);
	return (0);
}

int		ft_envlen(char *str, char **env, int *cpt)
{
	int i;
	int j;
	int k;

	i = 0;
	k = -1;
	while ((ft_isalpha(str[i]) == 1 || str[i] == '_') && str[i])
		i++;
	while (env[++k])
	{
		j = 0;
		while (env[k][j] != '=' && env[k][j])
			j++;
		if (ft_strncmp(str, env[k], i) == 0 && ft_strncmp(env[k], str, j) == 0)
		{
			*cpt = *cpt + ft_strlen(env[k]) - (j + 1);
			return (i);
		}
	}
	return (i);
}

void	ft_simpq_len(char *str, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
	{
		if (str[*i] == BACKS && ft_isbacks(str, *i) == 0)
			(*len)++;
		else if (str[*i] != BACKS)
			(*len)++;
		(*i)++;
	}
}

void	ft_doubleq_len(char *str, char **env, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 2 && str[*i])
	{
		if (str[*i] == '$' && ft_isbacks(str, (*i) - 1) == 0)
			(*i) += ft_envlen(&str[(*i) + 1], env, len);
		else if (str[*i] == BACKS && ft_isbacks(str, *i) == 0)
			(*len)++;
		else if (str[*i] != BACKS)
			(*len)++;
		(*i)++;
	}
}

int		ft_envcpylen(char *str, char **env)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_len(str, &i, &len);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			ft_doubleq_len(str, env, &i, &len);
		else if ((i == 0 && str[i] == '$') || (i > 0 && str[i] == '$' && ft_isbacks(str, i - 1) == 0))
			i += ft_envlen(&str[i + 1], env, &len);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			len++;
		else if (str[i] != BACKS)
			len++;
	}
	printf("len -> %d\n", len);
	return (len);
}

void	ft_simpq_cpy(char	*str, char *cpy, int *i, int *j)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
	{
		if (str[*i] == BACKS && ft_isbacks(str, *i) == 0)
			cpy[(*j)++] = str[*i];
		else if (str[*i] != BACKS)
			cpy[(*j)++] = str[*i];
		(*i)++;
	}
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
			while(env[k][++l])
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
		if (i < ft_strlen(str) - 1 && str[i] == '$' && str[i + 1] != ' ' && str[i +1] != DOUBQ && ft_isbacks(str, i - 1) == 0)
		{
			i += ft_varcpy(&str[i + 1], cpy, env, j);
		}
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[(*j)++] = str[i];
		else if (str[i] != BACKS)
			cpy[(*j)++] = str[i];
		i++;
	}
	return (i);
}

char	*ft_envcpy(char *str, char **env)
{
	int i;
	int j;
	char *cpy;

	i = -1;
	j = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_envcpylen(str, env) + 1))))
		return (NULL);
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
		|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_cpy(str, cpy, &i, &j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
		|| (i == 0 && str[i] == DOUBQ))
			i += ft_doubleq_cpy(&str[i], &cpy[0], env, &j);
		else if ((i == 0 && ft_strlen(str) > 1 && str[i] == '$' && str[i + 1] != ' ')
		|| (i > 0 && i < ft_strlen(str) - 1 && str[i] == '$' && str[i] + 1 != ' ' && ft_isbacks(str, i - 1) == 0 ))
			i += ft_varcpy(&str[i + 1],&cpy[0], env, &j);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			cpy[j++] = str[i];
		else if (str[i] != BACKS)
			cpy[j++] = str[i];
	}
	cpy[j] = '\0';
	printf("cpy -> %s\n", cpy);
	return (cpy);
}

/*
int		main(int argc, char **argv, char **env)
{
	char *str;
	int		fd;
	char *cpy;

	str = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
	cpy = ft_envcpy(str, env);
	//ft_printf("after -> %s\n", cpy);
	return (0);
}*/
