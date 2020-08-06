/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/06 08:57:45 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     find_fcts(t_cmds *cmd, t_env  *env)
{
    printf("We are here find_fcts\n");
    if (strcmp(cmd->str, "echo") == 0)
        return (ft_echo(cmd->args));
    else if (strcmp(cmd->str, "env") == 0)
        return (ft_env(cmd->args, env));
    else if (strcmp(cmd->str, "export") == 0)
        return (ft_export(cmd->args, env));
    else if (strcmp(cmd->str, "cd") == 0)
        return (ft_cd(cmd->args, env));
    else if (strcmp(cmd->str, "pwd") == 0)
        return (ft_pwd());
    else if (strcmp(cmd->str, "unset") == 0)
        return (ft_unset(cmd->args, env));
    else
        return (-1);
}