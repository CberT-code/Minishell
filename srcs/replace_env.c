/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 00:02:31 by user42            #+#    #+#             */
/*   Updated: 2020/06/19 15:29:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strdel(char **as)
{
	if (as)
	{
		if (*as)
			free(*as);
		*as = NULL;
	}
}

int		ft_del_name(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i + 1);
}

void	ft_is_envp(char *str, char **envp, int *j)
{
	int i;
	int k;
	int start;

	i = 0;
	k = -1;
	while (str[i] != '$' && str[i] != ' ' && str[i])
		i++;
	while (envp[++k])
	{
		if (ft_strncmp(str, envp[k], i) == 0)
		{
			start = ft_del_name(envp[k]);
			*j = *j + ft_strlen(&envp[k][start]) - i ;
		}
	}
}

int	ft_size_cpyenvp(char *str, char **envp)
{
	int i;
	int j;
	
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '$' || (str[i] == '$' && i == ft_strlen(str) - 1))
			j++;
		else
			ft_is_envp(&str[i + 1], envp, &j);
	}
	return (j);
}

char	*ft_search_envp(char *str, char **envp, int *k)
{
	char *cpy;
	int i;
	int j;
	int start;
	
	j = -1;
	i = -1;
	cpy = NULL;
	while (str[++i] != '$' && str[i] != ' ' && str[i])
		*k = *k + 1;
	while (envp[++j])
	{
		start = ft_del_name(envp[j]);
		if (ft_strncmp(str, envp[j], start - 1) == 0)
		{
			if (!(cpy = malloc(sizeof(char) * (ft_strlen(envp[j]) - start + 1))))
				return (NULL);
			i = 0;
			while (start < ft_strlen(envp[j]))
				cpy[i++] = envp[j][start++];
			cpy[i] = '\0';
			return (cpy);
		}
	}	
	return (cpy);
}

char *ft_convert_envp(char *str, char **envp)
{
	int i;
	int j;
	int k;
	char *cpy;
	char *env;

	i = -1;
	j = 0;

	if (!(cpy = (char *)malloc(sizeof(char) * (ft_size_cpyenvp(str, envp) + 1))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] != '$' || (str[i] == '$' && i == ft_strlen(str) - 1)
		|| (i < ft_strlen(str) - 2 && str[i] == '$' && str[i + 1] == ' '))
			cpy[j++] = str[i];
		else
		{
			env = ft_search_envp(&str[i + 1], envp, &i);
			if (!env && str[i + 1] == ' ')
				i++;
			k = 0;
			while(env && env[k])
				cpy[j++] = env[k++];
			ft_strdel(&env);
		}
	}
	cpy[j] = '\0';
	return(cpy);
}

int main(int argc, char **argv, char **envp)
{
	char *cpy = ft_convert_envp("je test la variable$PWD $HOME $ titi $", envp);
	printf("%s\n", cpy);
	free(cpy);
	return (0);
}
