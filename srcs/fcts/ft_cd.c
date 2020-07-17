/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/06/21 14:41:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_getenv(char *str, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (&env[i][ft_del_name(env[i])]);
	}
	return (NULL);
}

int ft_cd(char *str, char **env)
{
	if (!str || ft_strncmp(str, "~", 1) == 0)
	{
		if (chdir(ft_getenv("HOME", env)) != 0)
		{
			ft_putendl("Error - Environment variable $HOME not set");
			return (1);
		} 
		return (0);
	}
	if (chdir(str) != 0)
	{
		ft_putendl("Error - No such file or directory");
		return (1);
	}
	return (0);
}

/*
int main(int argc, char **arg, char **env)
{
	char cpy[1024];

	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	ft_cd("../", env);
	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	ft_cd("~", env);
	getcwd(cpy, sizeof(cpy));
	printf("%s\n", cpy);
	return (0);
}*/
