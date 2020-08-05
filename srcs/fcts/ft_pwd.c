/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 19:36:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl(cwd);
		return (0);
	}
	ft_putstr("pwd : Error - Failed to get pwd");
	return (-1);
}
