/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 22:26:44 by cbertola         ###   ########.fr       */
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
	return (2);
}
